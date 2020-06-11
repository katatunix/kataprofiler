using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;
using System.IO;
using System.Collections;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace KataProfiler
{
	public partial class FormMain : Form
	{
		#region Member variables

		private static Font m_sHighlightFont = new Font("Calibri", 11.75F, FontStyle.Regular);
		private string[] m_sColsName = new string[] { "idx", "x", "y", "z", "w" };

		private Dictionary<int, Bitmap> m_bitmapPool = new Dictionary<int, Bitmap>();
		private Dictionary<int, TabControl> m_vertexDataTabControlPool = new Dictionary<int, TabControl>();
		private Dictionary<int, List<uint>> m_inUseVboIdPool = new Dictionary<int, List<uint>>();

		private int m_screenShotWidth	= 0;
		private int m_screenShotHeight	= 0;

		private BackgroundWorker m_capturingBgrWorker = new BackgroundWorker();

		private FormCapturing m_formCapturing = null;

		ListViewItemComparer_Textures	m_lvicTextures;
		ListViewItemComparer_Programs	m_lvicPrograms;
		ListViewItemComparer_Vbos		m_lvicVbos;

		#endregion	

		public FormMain()
		{
			InitializeComponent();

			m_capturingBgrWorker.WorkerSupportsCancellation = true;
			m_capturingBgrWorker.WorkerReportsProgress = true;
			m_capturingBgrWorker.DoWork += new DoWorkEventHandler(capturing_DoWork);
			m_capturingBgrWorker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(capturing_RunWorkerCompleted);
			m_capturingBgrWorker.ProgressChanged += new ProgressChangedEventHandler(capturing_ProgressChanged);

			//======================================================================================================
			m_lvicTextures = new ListViewItemComparer_Textures(listViewTextures);
			listViewTextures.ListViewItemSorter = m_lvicTextures;
			//======================================================================================================
			m_lvicPrograms = new ListViewItemComparer_Programs(listViewPrograms);
			listViewPrograms.ListViewItemSorter = m_lvicPrograms;
			//======================================================================================================
			m_lvicVbos = new ListViewItemComparer_Vbos(listViewVbos);
			listViewVbos.ListViewItemSorter = m_lvicVbos;
			//======================================================================================================
		}

		#region GUI events

		private void FormMain_Load(object sender, EventArgs e)
		{
			Client.getInstance();
			comboBoxZoomSS.SelectedIndex = 0;
			comboBoxPlatform.SelectedIndex = 0;
		}

		private void buttonCapture_Click(object sender, EventArgs e)
		{
			doCapture();
		}

		private void onCaptureCancel()
		{
			Client.getInstance().cancelCaptureFrame();
		}

		private void listBoxRenderCommands_SelectedIndexChanged(object sender, EventArgs e)
		{
			int index = listBoxRenderCommands.SelectedIndex;
			if (index < 0) return;

			int lastIndex = listBoxRenderCommands.Items.Count - 2;

			Client client = Client.getInstance();
			Message[] listCommands = client.ListCommands;
			int[] listIndexes = client.ListRenderCommandIndexes;

			//=============================================================================================
			// Fill the listBoxSubCommands
			//=============================================================================================
			listBoxSubCommands.Items.Clear();
			
			int start = index == 0 ? 0 : listIndexes[index - 1] + 1;

			int subCommandsCount = listIndexes[index] - start;
			string[] arr = null;
			if (subCommandsCount > 0) arr = new string[subCommandsCount];
			for (int i = start; i < listIndexes[index]; i++)
			{
				arr[i - start] = listCommands[i].toString();
			}
			if (arr != null)
				listBoxSubCommands.Items.AddRange(arr);

			listBoxSubCommands.SelectedIndex = -1;

			//=============================================================================================
			// Show screen shot and vertex data
			//=============================================================================================
			Message cmd = client.ListCommands[listIndexes[index]];
			KPMessageType type = (KPMessageType)cmd.Type;

			tabPageVertexData.Controls.Clear();
			List<uint> list_ArrayBuffer_VboId = null;

			bool isDrawnCommand = false;

			if (type == KPMessageType.KMT_glDrawElements || type == KPMessageType.KMT_glDrawArrays ||
				type == KPMessageType.KMT_glClear)
			{
				#region Show screen shot
				{
					Bitmap bmp = null;
					MyBinStream stream = new MyBinStream(cmd.Data);

					if (type == KPMessageType.KMT_glDrawElements)
					{
						stream.readUInt(); // fbo
						stream.readUInt(); // mode
						stream.readInt(); // count
						stream.readUInt(); // type
						stream.readInt(); // indices
						stream.readFloat(); // zNear
						stream.readFloat(); // zFar
					}
					else if (type == KPMessageType.KMT_glDrawArrays)
					{
						stream.readUInt(); // fbo
						stream.readUInt(); // mode
						stream.readInt(); // first
						stream.readInt(); // count
						stream.readFloat(); // zNear
						stream.readFloat(); // zFar
					}
					else if (type == KPMessageType.KMT_glClear)
					{
						stream.readUInt(); // fbo
						stream.readUInt(); // mask
					}

					m_screenShotWidth = stream.readInt();
					m_screenShotHeight = stream.readInt();

					if (m_bitmapPool.ContainsKey(index))
					{
						bmp = m_bitmapPool[index];
					}
					else
					{
						int widthScaled = stream.readInt();
						int heightScaled = stream.readInt();

						int imageLen = stream.readInt();
						int curPos = stream.CurrentPosition;
						//bmp = Utils.makeBitmap_RGBA(widthScaled, heightScaled, cmd.Data, curPos, true);
						bmp = Utils.makeBitmap_RGB(widthScaled, heightScaled, cmd.Data, curPos, true);

						m_bitmapPool.Add(index, bmp);
					}
					stream.close();

					pictureBoxScreenShot.Dock = DockStyle.None;

					zoomSS();

					pictureBoxScreenShot.Image = bmp;
				}
				#endregion

				#region Show vertex data
				if (type == KPMessageType.KMT_glDrawElements || type == KPMessageType.KMT_glDrawArrays)
				{
					isDrawnCommand = true;

					TabControl tabControlVertexData = null;

					if (m_vertexDataTabControlPool.ContainsKey(index))
					{
						tabControlVertexData = m_vertexDataTabControlPool[index];
						list_ArrayBuffer_VboId = m_inUseVboIdPool[index];
					}
					else
					{
						list_ArrayBuffer_VboId = new List<uint>();

						tabControlVertexData = new TabControl();
						tabControlVertexData.Dock = System.Windows.Forms.DockStyle.Fill;
						tabControlVertexData.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
						tabControlVertexData.Location = new System.Drawing.Point(3, 4);
						tabControlVertexData.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
						tabControlVertexData.Name = "tabControlVertexData";
						tabControlVertexData.SelectedIndex = 0;

						#region
						
						MyBinStream stream = new MyBinStream(cmd.Data);

						int count, first;

						if (type == KPMessageType.KMT_glDrawElements)
						{
							stream.readUInt(); // fbo
							stream.readUInt(); // mode
							count = stream.readInt(); // count
							stream.readUInt(); // type
							stream.readInt(); // indices
						}
						else // type == KPMessageType.KMT_glDrawArrays
						{
							stream.readUInt(); // fbo
							stream.readUInt(); // mode
							first = stream.readInt(); // first
							count = stream.readInt(); // count
						}
						stream.readFloat(); // zNear
						stream.readFloat(); // zFar

						int width = stream.readInt();
						int height = stream.readInt();
						int widthScaled = stream.readInt();
						int heightScaled = stream.readInt();
						int imageLen = stream.readInt();

						stream.skip(imageLen);

						int attCount = stream.readInt();

						tabControlVertexData.TabPages.Clear();

						for (int i = 0; i < attCount; i++)
						{
							#region Process attribute

							byte enableVertexAttribArray = stream.readByte();

							int location = stream.readInt();
							int components = stream.readInt();

							TabPage tp = new TabPage("Loc " + location +
								(enableVertexAttribArray == 0 ? " (non-array)" : "")
							);

							ListView view = new ListView();
							#region
							view.Dock = DockStyle.Fill;
							view.BorderStyle = BorderStyle.Fixed3D;
							view.HeaderStyle = ColumnHeaderStyle.Nonclickable;
							view.FullRowSelect = true;
							view.GridLines = true;
							view.MultiSelect = false;
							view.ShowGroups = false;
							view.View = View.Details;

							ColumnHeader[] columnHeaders = new ColumnHeader[components + 1];
							for (int k = 0; k <= components; k++)
							{
								columnHeaders[k] = new ColumnHeader();
								columnHeaders[k].Text = m_sColsName[k];
							}
							view.Columns.AddRange(columnHeaders);
							#endregion

							if (enableVertexAttribArray == 0)
							{
								string[] row = new string[components + 1];
								row[0] = "#";
								for (int k = 1; k <= components; k++)
								{
									row[k] = stream.readFloat().ToString();
								}
								ListViewItem item = new ListViewItem(row);
								view.Items.Add(item);
							}
							else
							{
								byte normalized = stream.readByte();
								if (normalized == 1)
								{
									tp.Text += " (nm)";
								}

								uint vboId = stream.readUInt();
								list_ArrayBuffer_VboId.Add(vboId);

								uint dataType = stream.readUInt();

								ListViewItem[] itemArray = null;
								if (count > 0) itemArray = new ListViewItem[count];

								#region
								for (int j = 0; j < count; j++)
								{
									string[] row = new string[components + 1];

									row[0] = j.ToString();

									for (int k = 1; k <= components; k++)
									{
										switch (dataType)
										{
											case gl.GL_BYTE:
												{
													sbyte val = stream.readSByte();
													row[k] = val.ToString();
													if (normalized == 1)
													{
														row[k] += " (" + ( (val + 128.0f) / 255.0f * 2.0f - 1.0f ) + ")";
													}
													break;
												}
											case gl.GL_UNSIGNED_BYTE:
												{
													byte val = stream.readByte();
													row[k] = val.ToString();
													if (normalized == 1)
													{
														row[k] += " (" + (val / 255.0f) + ")";
													}
													break;
												}
											case gl.GL_SHORT:
												{
													Int16 val = stream.readShort();
													row[k] = val.ToString();
													if (normalized == 1)
													{
														row[k] += " (" + ( (val + 32768.0f) / 65535.0f * 2.0f - 1.0f ) + ")";
													}
													break;
												}
											case gl.GL_UNSIGNED_SHORT:
												{
													UInt16 val = stream.readUShort();
													row[k] = val.ToString();
													if (normalized == 1)
													{
														row[k] += " (" + (val / 65535.0f) + ")";
													}
													break;
												}
											case gl.GL_FLOAT:
												{
													row[k] = stream.readFloat().ToString();
													break;
												}
											case gl.GL_FIXED:
												{
													//Utils.assert(false);
													row[k] = stream.readInt().ToString();
													break;
												}
										}

									}
									itemArray[j] = new ListViewItem(row);
								}
								#endregion

								if (itemArray != null)
									view.Items.AddRange(itemArray);
							}

							tp.Controls.Add(view);

							#endregion

							tabControlVertexData.TabPages.Add(tp);
						}

						stream.close();
						#endregion

						m_vertexDataTabControlPool.Add(index, tabControlVertexData);
						m_inUseVboIdPool.Add(index, list_ArrayBuffer_VboId);
					}

					tabPageVertexData.Controls.Add(tabControlVertexData);
				}
				#endregion
			}
			else if (type == KPMessageType.KMT_NONE)
			{
				pictureBoxScreenShot.Width = 0;
				pictureBoxScreenShot.Height = 0;
				pictureBoxScreenShot.Dock = DockStyle.Fill;
				pictureBoxScreenShot.Image = null;
			}

			//=============================================================================================
			// Fill the objects list
			//=============================================================================================
			client.makeStateMachine(listIndexes[index]);
			
			#region Textures list
			{
				listViewTextures.Items.Clear();

				List<Texture> textures = client.CurrentStateMachine.ListTextures;

				int texSumBytes = 0;
				List<uint> listTexId = isDrawnCommand ? client.CurrentStateMachine.getDrawingTextures() : new List<uint>();

				ListViewItem[] itemArray = null;
				if (textures.Count > 0)
				{
					itemArray = new ListViewItem[textures.Count];
				}

				for (int i = 0; i < textures.Count; i++)
				{
					texSumBytes += textures[i].SizeInBytes;

					bool inUse = listTexId.Contains(textures[i].Id);

					Mipmap mip = textures[i].Mipmaps[0];

					bool is2n = Utils.isPowerOf2(mip.Width) && Utils.isPowerOf2(mip.Height);
					bool isSquare = mip.Width == mip.Height;

					itemArray[i] = new ListViewItem(new string[] {
						textures[i].Id.ToString(),
						mip.Width.ToString(),
						mip.Height.ToString(),
						mip.FormatName,
						textures[i].MipmapCount.ToString(),
						mip.calculateSize().ToString(),
						(mip.Width * mip.Height).ToString(),
						is2n ? "Yes" : "No",
						isSquare ? "Yes" : "No",
						textures[i].TexType == KPTextureType.TEX_2D ? "2D" : "Cube",
						client.CurrentStateMachine.getTexUnitsOfTexId(textures[i].Id),

						inUse ? "Yes" : "No"
					});

					if ( inUse )
					{
					    highlightItem(itemArray[i]);
					}
				}
				if (itemArray != null) listViewTextures.Items.AddRange(itemArray);

				m_lvicTextures.setColumnIndexToSort(columnHeader_TexInUse.Index);
				listViewTextures.Sort();

				labelTexturesSummary.Text = textures.Count + " texture(s) / " + Utils.getDynamicSize(texSumBytes);

				panelTextures.Visible = true;
			}
			#endregion
			
			#region Programs list
			{
				listViewPrograms.Items.Clear();
				
				List<Program> programs = client.CurrentStateMachine.ListPrograms;
				uint usingProgId = isDrawnCommand ? client.CurrentStateMachine.CurrentProgId : 0;

				ListViewItem usingItem = null;
				ListViewItem[] itemArray = null;
				if (programs.Count > 0)
				{
					itemArray = new ListViewItem[programs.Count];
				}
				
				for (int i = 0; i < programs.Count; i++)
				{
					itemArray[i] = new ListViewItem(new string[] {
						programs[i].Id.ToString(),
						programs[i].VsId.ToString(),
						programs[i].FsId.ToString()
					});

					if (usingProgId == programs[i].Id)
					{
						usingItem = itemArray[i];
						highlightItem(itemArray[i]);
					}
				}
				if (itemArray != null) listViewPrograms.Items.AddRange(itemArray);
				
				if (usingItem != null) listViewPrograms.EnsureVisible(usingItem.Index);

				labelProgramsSummary.Text = programs.Count + " program(s)";
				
				panelPrograms.Visible = true;
			}
			#endregion
			
			#region Vbos list
			{
				listViewVbos.Items.Clear();
				
				List<Vbo> vbos = client.CurrentStateMachine.ListVbos;

				uint bindingVboId_ElementArrayBuffer = isDrawnCommand ? client.CurrentStateMachine.CurrentVboId_ElementArrayBuffer : 0;

				ListViewItem[] itemArray = null;
				if (vbos.Count > 0)
				{
					itemArray = new ListViewItem[vbos.Count];
				}

				int sum_Size = 0;

				for (int i = 0; i < vbos.Count; i++)
				{
					bool inUse_ArrayBuffer = list_ArrayBuffer_VboId == null || !isDrawnCommand ?
												false : list_ArrayBuffer_VboId.Contains(vbos[i].Id);

					bool inUse_ElementArrayBuffer = !isDrawnCommand ? false : bindingVboId_ElementArrayBuffer == vbos[i].Id;

					sum_Size += vbos[i].Size;

					itemArray[i] = new ListViewItem(new string[] {
						vbos[i].Id.ToString(),

						vbos[i].Size.ToString(),
						gl.getString(vbos[i].Usage),

						inUse_ArrayBuffer || inUse_ElementArrayBuffer ? "Yes" : "No"
					});

					if (inUse_ArrayBuffer && inUse_ElementArrayBuffer)
					{
						highlightItem(itemArray[i], Color.Red);
					}
					else if (inUse_ArrayBuffer)
					{
						highlightItem(itemArray[i]);
					}
					else if (inUse_ElementArrayBuffer)
					{
						highlightItem(itemArray[i], Color.Brown);
					}
				}

				if (itemArray != null) listViewVbos.Items.AddRange(itemArray);

				m_lvicVbos.setColumnIndexToSort(columnHeader_VboInUse.Index);
				listViewVbos.Sort();

				labelVbosSummary.Text = string.Format("{0} vbo(s) / {1}", vbos.Count, Utils.getDynamicSize(sum_Size));

				panelVbos.Visible = true;
			}
			#endregion
			
			//Utils.gc();
		}

		private void listViewTextures_ItemActivate(object sender, EventArgs e)
		{
			string texId = listViewTextures.FocusedItem.Text;

			//Utils.gc();

			Client client = Client.getInstance();

			FormObjectDetail form = new FormObjectDetail();

			UcTexture ucTexture = new UcTexture();
			form.Controls.Add(ucTexture);

			Texture tex = client.CurrentStateMachine.getTextureById(uint.Parse(texId));

			form.Text = "Texture :: id = " + (tex == null ? "ZERO" : tex.Id.ToString());
			ucTexture.applyTex(tex);
			form.Show(this);
		}
		private void listViewTextures_ColumnClick(object sender, ColumnClickEventArgs e)
		{
			m_lvicTextures.setColumnIndexToSort(e.Column);
			listViewTextures.Sort();
		}
		
		private void listViewPrograms_ItemActivate(object sender, EventArgs e)
		{
			string progId = listViewPrograms.FocusedItem.Text;
			//Utils.gc();

			Client client = Client.getInstance();

			FormObjectDetail form = new FormObjectDetail();
			UcProgram ucProg = new UcProgram(textBoxServer.Text, int.Parse(textBoxPort.Text));
			form.Controls.Add(ucProg);

			Program prog = client.CurrentStateMachine.getProgramById(uint.Parse(progId));
			if (prog != null)
			{
				Shader vs = client.CurrentStateMachine.getShaderById(prog.VsId);
				string vsSource = vs == null ? "" : vs.Source;
	
				Shader fs = client.CurrentStateMachine.getShaderById(prog.FsId);
				string fsSource = fs == null ? "" : fs.Source;

				ucProg.applyProg(prog, vsSource, fsSource);
			}

			form.Show(this);
		}
		private void listViewPrograms_ColumnClick(object sender, ColumnClickEventArgs e)
		{
			m_lvicPrograms.setColumnIndexToSort(e.Column);
			listViewPrograms.Sort();
		}

		private void listViewVbos_ItemActivate(object sender, EventArgs e)
		{
			// Nothing to do with Vbo
		}
		private void listViewVbos_ColumnClick(object sender, ColumnClickEventArgs e)
		{
			m_lvicVbos.setColumnIndexToSort(e.Column);
			listViewVbos.Sort();
		}

		private void comboBoxZoomSS_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (m_screenShotWidth == 0) return;
			zoomSS();
		}

		private void comboBoxPlatform_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (comboBoxPlatform.SelectedIndex == 0)
			{
				Utils.usePlatform_Android();
			}
			else if (comboBoxPlatform.SelectedIndex == 1)
			{
				Utils.usePlatform_Tizen();
			}
			else
			{
				Utils.usePlatform_Win32();
			}
		}

		private void pictureBoxScreenShot_MouseClick(object sender, MouseEventArgs e)
		{
			panelScreenShot.Focus();
		}

		#endregion

		#region m_capturingBgrWorker events

		private void capturing_DoWork(object sender, DoWorkEventArgs e)
		{
			BackgroundWorker worker = sender as BackgroundWorker;
			e.Result = null;

			try
			{
				if ( Client.getInstance().captureFrame(
					textBoxServer.Text,
					int.Parse(textBoxPort.Text),
					checkBoxScaleSS.Checked,
					m_capturingBgrWorker) )
				{
					e.Cancel = true;
				}
			}
			catch (Exception ex)
			{
				e.Result = ex.Message;
			}
		}

		private void capturing_ProgressChanged(object sender, ProgressChangedEventArgs e)
		{
			m_formCapturing.onReceiveMsg(e.UserState as Message);
		}

		private void capturing_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
		{
			m_formCapturing.Close();

			if (e.Cancelled)
			{
				
			}
			else if (e.Error != null)
			{
				//Utils.gc();
				MessageBox.Show(this, e.Error.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
			else if (e.Result != null)
			{
				//Utils.gc();
				MessageBox.Show(this, e.Result.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
			else
			{
				showGLCommands();
				//Utils.gc();
			}
		}
		
		#endregion

		#region Helpers

		private void clearAllGUI()
		{
			listViewTextures.Items.Clear();
			panelTextures.Visible = false;

			listViewPrograms.Items.Clear();
			panelPrograms.Visible = false;

			listViewVbos.Items.Clear();
			panelVbos.Visible = false;

			//

			listBoxSubCommands.Items.Clear();
			listBoxRenderCommands.Items.Clear();

			pictureBoxScreenShot.Width = 0;
			pictureBoxScreenShot.Height = 0;
			pictureBoxScreenShot.Dock = DockStyle.Fill;
			pictureBoxScreenShot.Image = null;

			tabPageVertexData.Controls.Clear();

			m_bitmapPool.Clear();
			m_vertexDataTabControlPool.Clear();
			m_inUseVboIdPool.Clear();
		}

		private void doCapture()
		{
			clearAllGUI();

			m_formCapturing = null;

			//Utils.gc();

			m_formCapturing = new FormCapturing(new CaptureCancelEventHandler(onCaptureCancel));

			m_capturingBgrWorker.RunWorkerAsync();
			m_formCapturing.ShowDialog(this);
		}

		private void showGLCommands()
		{
			listBoxRenderCommands.Items.Clear();
			listBoxSubCommands.Items.Clear();

			Client client = Client.getInstance();
			string[] arr = null;
			if (client.CountRenderCommandIndexes > 0) arr = new string[client.CountRenderCommandIndexes];
			for (int i = 0; i < client.CountRenderCommandIndexes; i++)
			{
				Message msg = client.ListCommands[client.ListRenderCommandIndexes[i]];
				arr[i] = msg.toString();
			}
			if (arr != null)
				listBoxRenderCommands.Items.AddRange(arr);

			if (listBoxRenderCommands.Items.Count >= 2)
				listBoxRenderCommands.SelectedIndex = listBoxRenderCommands.Items.Count - 2;
			else if (listBoxRenderCommands.Items.Count >= 1)
				listBoxRenderCommands.SelectedIndex = listBoxRenderCommands.Items.Count - 1;
			else
				listBoxRenderCommands.SelectedIndex = -1;
		}

		private void highlightItem(ListViewItem item)
		{
			highlightItem(item, Color.Blue);
		}

		private void highlightItem(ListViewItem item, Color c)
		{
			item.Font = m_sHighlightFont;
			item.ForeColor = c;
		}

		private void zoomSS()
		{
			if (comboBoxZoomSS.SelectedIndex == 0) // 100 %
			{
				pictureBoxScreenShot.Width = m_screenShotWidth;
				pictureBoxScreenShot.Height = m_screenShotHeight;
			}
			else if (comboBoxZoomSS.SelectedIndex == 1) // 50 %
			{
				pictureBoxScreenShot.Width = m_screenShotWidth / 2;
				pictureBoxScreenShot.Height = m_screenShotHeight / 2;
			}
			else if (comboBoxZoomSS.SelectedIndex == 2) // 25 %
			{
				pictureBoxScreenShot.Width = m_screenShotWidth / 4;
				pictureBoxScreenShot.Height = m_screenShotHeight / 4;
			}
		}

		#endregion

		#region ListViewItemComparer

		abstract class ListViewItemComparer : IComparer
		{
			protected int m_columnIndexToSort;
			protected ListView m_listView;
			protected bool m_isAscending;

			public ListViewItemComparer(ListView listView)
			{
				m_columnIndexToSort = 0;
				m_listView = listView;
				m_isAscending = true;
			}

			public void setColumnIndexToSort(int columnIndexToSort)
			{
				if (m_columnIndexToSort == columnIndexToSort)
				{
					m_isAscending = !m_isAscending;
				}
				else
				{
					m_isAscending = true;
					m_columnIndexToSort = columnIndexToSort;
				}
			}

			public abstract int Compare(object x, object y);
		}

		class ListViewItemComparer_Textures : ListViewItemComparer
		{
			public ListViewItemComparer_Textures(ListView listView)
				: base(listView)
			{
			}

			public override int Compare(object x, object y)
			{
				int returnVal = -1;

				string columnNameToSort = m_listView.Columns[m_columnIndexToSort].Text;

				bool allowSortToggle = true;

				switch (columnNameToSort)
				{
					case "Id":
					case "W":
					case "H":
					case "Bytes":
					case "Pixels":
					case "Mips":
					{
						int xInt = int.Parse( ((ListViewItem)x).SubItems[m_columnIndexToSort].Text );
						int yInt = int.Parse(((ListViewItem)y).SubItems[m_columnIndexToSort].Text);

						if (xInt < yInt) returnVal = -1;
						else if (xInt == yInt) returnVal = 0;
						else returnVal = 1;

						break;
					}

					case "Type":
					case "Format":
					case "In use?":
					case "2^n?":
					case "Square?":
					case "Unit(s)":
					{
						returnVal = String.Compare(
							((ListViewItem)x).SubItems[m_columnIndexToSort].Text,
							((ListViewItem)y).SubItems[m_columnIndexToSort].Text
						);
						if (columnNameToSort == "In use?")
						{
							returnVal = -returnVal;
							allowSortToggle = false;
						}
						break;
					}
				}
				
				if (!allowSortToggle) return returnVal;
				return m_isAscending ? returnVal : -returnVal;
			}
		}

		class ListViewItemComparer_Programs : ListViewItemComparer
		{
			public ListViewItemComparer_Programs(ListView listView)
				: base(listView)
			{
			}

			public override int Compare(object x, object y)
			{
				int returnVal = -1;
	
				int xInt = int.Parse(((ListViewItem)x).SubItems[m_columnIndexToSort].Text);
				int yInt = int.Parse(((ListViewItem)y).SubItems[m_columnIndexToSort].Text);

				if (xInt < yInt) returnVal = -1;
				else if (xInt == yInt) returnVal = 0;
				else returnVal = 1;

				return m_isAscending ? returnVal : -returnVal;
			}
		}

		class ListViewItemComparer_Vbos : ListViewItemComparer
		{
			public ListViewItemComparer_Vbos(ListView listView) : base(listView)
			{
			}

			public override int Compare(object x, object y)
			{
				int returnVal = -1;

				bool allowSortToggle = true;

				string columnNameToSort = m_listView.Columns[m_columnIndexToSort].Text;

				if (columnNameToSort == "Usage" || columnNameToSort == "In use?")
				{
					returnVal = String.Compare(
						((ListViewItem)x).SubItems[m_columnIndexToSort].Text,
						((ListViewItem)y).SubItems[m_columnIndexToSort].Text
					);
					if (columnNameToSort == "In use?")
					{
						returnVal = -returnVal;
						allowSortToggle = false;
					}
				}
				else
				{
					int xInt = int.Parse(((ListViewItem)x).SubItems[m_columnIndexToSort].Text);
					int yInt = int.Parse(((ListViewItem)y).SubItems[m_columnIndexToSort].Text);

					if (xInt < yInt) returnVal = -1;
					else if (xInt == yInt) returnVal = 0;
					else returnVal = 1;
				}

				if (!allowSortToggle) return returnVal;
				return m_isAscending ? returnVal : -returnVal;
			}
		}

		#endregion

	}
}
