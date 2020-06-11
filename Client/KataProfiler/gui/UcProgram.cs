using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace KataProfiler
{
	public partial class UcProgram : UserControl
	{
		private const int PADDING = 8;

		private string m_host;
		private int m_port;

		private Program m_prog;
		private string m_vsSource;
		private string m_fsSource;

		private string m_backupVsSource;
		private string m_backupFsSource;

		public UcProgram(string host, int port)
		{
			InitializeComponent();

			this.Dock = DockStyle.Fill;

			m_prog = new Program();

			alignLeftPanel();

			m_host = host;
			m_port = port;
		}

		public void applyProg(Program prog, string vsSource, string fsSource)
		{
			m_prog.copyFrom(prog);
			m_vsSource = vsSource;
			m_fsSource = fsSource;

			m_backupVsSource = vsSource;
			m_backupFsSource = fsSource;

			fastColoredTextBoxVS.Text = m_vsSource;
			fastColoredTextBoxFS.Text = m_fsSource;

			string txt = "";
			
			Var[] vars = m_prog.Attributes;
			int count = m_prog.AttributesCount;
			for (int i = 0; i < count; i++)
			{
				txt += vars[i].toString() + ";" + Environment.NewLine + Environment.NewLine;
			}
			richTextBoxATT.Text = txt;

			txt = "";

			vars = m_prog.Uniforms;
			count = m_prog.UniformsCount;
			for (int i = 0; i < count; i++)
			{
				txt += vars[i].toString() + ";" + Environment.NewLine + Environment.NewLine;
			}
			richTextBoxUNI.Text = txt;

			this.Parent.Text = "Program :: id = " + m_prog.Id;
			tabPageVS.Text += " (" + m_prog.VsId + ")";
			tabPageFS.Text += " (" + m_prog.FsId + ")";
		}

		private void buttonSend_Click(object sender, EventArgs e)
		{
			try
			{
				Client.getInstance().modifyProgram(
					m_prog.Id,
					m_prog.VsId,
					m_prog.FsId,

					fastColoredTextBoxVS.Text,
					fastColoredTextBoxFS.Text,

					m_host,
					m_port
				);

				fastColoredTextBoxOutput.Text = "Success!";
				MessageBox.Show(this, "Success!", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
			}
			catch (Exception ex)
			{
				fastColoredTextBoxOutput.Text = ex.Message;
				MessageBox.Show(this, ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}

		private void splitContainer1_Panel1_SizeChanged(object sender, EventArgs e)
		{
			alignLeftPanel();
		}

		private void alignLeftPanel()
		{
			int w = splitContainerMaster.Panel1.Width;
			int h = splitContainerMaster.Panel1.Height;

			int rttHeight = (h - 5 * PADDING - labelATT.Height - labelUNI.Height) / 2;
			int rttWidth = w - 2 * PADDING;

			richTextBoxATT.Height = rttHeight;
			richTextBoxUNI.Height = rttHeight;

			richTextBoxATT.Width = rttWidth; richTextBoxATT.Left = PADDING;
			richTextBoxUNI.Width = rttWidth; richTextBoxUNI.Left = PADDING;

			int currentTop = PADDING;
			labelATT.Top = currentTop;

			currentTop += labelATT.Height + PADDING;
			richTextBoxATT.Top = currentTop;

			currentTop += richTextBoxATT.Height + PADDING;
			labelUNI.Top = currentTop;

			currentTop += labelUNI.Height + PADDING;
			richTextBoxUNI.Top = currentTop;
		}

		private void buttonRevert_Click(object sender, EventArgs e)
		{
			if (tabControl.SelectedTab == tabPageVS)
			{
				fastColoredTextBoxVS.Text = m_backupVsSource;
			}
			else
			{
				fastColoredTextBoxFS.Text = m_backupFsSource;
			}
		}

		private void buttonRevertAll_Click(object sender, EventArgs e)
		{
			fastColoredTextBoxVS.Text = m_backupVsSource;
			fastColoredTextBoxFS.Text = m_backupFsSource;
		}
	}
}
