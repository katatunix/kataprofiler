namespace KataProfiler
{
	partial class FormMain
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
			this.buttonCapture = new System.Windows.Forms.Button();
			this.listBoxRenderCommands = new System.Windows.Forms.ListBox();
			this.listBoxSubCommands = new System.Windows.Forms.ListBox();
			this.tabControlObjectsList = new System.Windows.Forms.TabControl();
			this.tabPageTextures = new System.Windows.Forms.TabPage();
			this.panelTextures = new System.Windows.Forms.Panel();
			this.listViewTextures = new System.Windows.Forms.ListView();
			this.columnHeader_TexId = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_W = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_H = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_Format = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_Mips = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_Bytes = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_Pixels = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_2n = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_Square = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_TexType = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_TexUnit = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_TexInUse = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.labelTexturesSummary = new System.Windows.Forms.Label();
			this.tabPagePrograms = new System.Windows.Forms.TabPage();
			this.panelPrograms = new System.Windows.Forms.Panel();
			this.labelProgramsSummary = new System.Windows.Forms.Label();
			this.listViewPrograms = new System.Windows.Forms.ListView();
			this.columnHeader_ProgId = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_VS = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_FS = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.tabPageVBOs = new System.Windows.Forms.TabPage();
			this.panelVbos = new System.Windows.Forms.Panel();
			this.labelVbosSummary = new System.Windows.Forms.Label();
			this.listViewVbos = new System.Windows.Forms.ListView();
			this.columnHeader_VboId = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_Size = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_Usage = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader_VboInUse = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.panelScreenShot = new System.Windows.Forms.Panel();
			this.pictureBoxScreenShot = new System.Windows.Forms.PictureBox();
			this.splitContainerLeft = new System.Windows.Forms.SplitContainer();
			this.splitContainerOpenGLCalls = new System.Windows.Forms.SplitContainer();
			this.tabControlRenderCalls = new System.Windows.Forms.TabControl();
			this.tabPageRenderCalls = new System.Windows.Forms.TabPage();
			this.tabControl_API_Calls = new System.Windows.Forms.TabControl();
			this.tabPageAPICalls = new System.Windows.Forms.TabPage();
			this.tabPageVertexData = new System.Windows.Forms.TabPage();
			this.splitContainerMaster = new System.Windows.Forms.SplitContainer();
			this.checkBoxScaleSS = new System.Windows.Forms.CheckBox();
			this.textBoxPort = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.textBoxServer = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.comboBoxZoomSS = new System.Windows.Forms.ComboBox();
			this.comboBoxPlatform = new System.Windows.Forms.ComboBox();
			this.tabControlObjectsList.SuspendLayout();
			this.tabPageTextures.SuspendLayout();
			this.panelTextures.SuspendLayout();
			this.tabPagePrograms.SuspendLayout();
			this.panelPrograms.SuspendLayout();
			this.tabPageVBOs.SuspendLayout();
			this.panelVbos.SuspendLayout();
			this.panelScreenShot.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBoxScreenShot)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.splitContainerLeft)).BeginInit();
			this.splitContainerLeft.Panel1.SuspendLayout();
			this.splitContainerLeft.Panel2.SuspendLayout();
			this.splitContainerLeft.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainerOpenGLCalls)).BeginInit();
			this.splitContainerOpenGLCalls.Panel1.SuspendLayout();
			this.splitContainerOpenGLCalls.Panel2.SuspendLayout();
			this.splitContainerOpenGLCalls.SuspendLayout();
			this.tabControlRenderCalls.SuspendLayout();
			this.tabPageRenderCalls.SuspendLayout();
			this.tabControl_API_Calls.SuspendLayout();
			this.tabPageAPICalls.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainerMaster)).BeginInit();
			this.splitContainerMaster.Panel1.SuspendLayout();
			this.splitContainerMaster.Panel2.SuspendLayout();
			this.splitContainerMaster.SuspendLayout();
			this.SuspendLayout();
			// 
			// buttonCapture
			// 
			this.buttonCapture.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.buttonCapture.Location = new System.Drawing.Point(5, 2);
			this.buttonCapture.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
			this.buttonCapture.Name = "buttonCapture";
			this.buttonCapture.Size = new System.Drawing.Size(101, 30);
			this.buttonCapture.TabIndex = 0;
			this.buttonCapture.Text = "Capture";
			this.buttonCapture.UseVisualStyleBackColor = true;
			this.buttonCapture.Click += new System.EventHandler(this.buttonCapture_Click);
			// 
			// listBoxRenderCommands
			// 
			this.listBoxRenderCommands.Dock = System.Windows.Forms.DockStyle.Fill;
			this.listBoxRenderCommands.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.listBoxRenderCommands.FormattingEnabled = true;
			this.listBoxRenderCommands.HorizontalScrollbar = true;
			this.listBoxRenderCommands.IntegralHeight = false;
			this.listBoxRenderCommands.ItemHeight = 15;
			this.listBoxRenderCommands.Location = new System.Drawing.Point(3, 3);
			this.listBoxRenderCommands.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
			this.listBoxRenderCommands.Name = "listBoxRenderCommands";
			this.listBoxRenderCommands.Size = new System.Drawing.Size(374, 256);
			this.listBoxRenderCommands.TabIndex = 0;
			this.listBoxRenderCommands.SelectedIndexChanged += new System.EventHandler(this.listBoxRenderCommands_SelectedIndexChanged);
			// 
			// listBoxSubCommands
			// 
			this.listBoxSubCommands.Dock = System.Windows.Forms.DockStyle.Fill;
			this.listBoxSubCommands.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.listBoxSubCommands.FormattingEnabled = true;
			this.listBoxSubCommands.HorizontalScrollbar = true;
			this.listBoxSubCommands.IntegralHeight = false;
			this.listBoxSubCommands.ItemHeight = 15;
			this.listBoxSubCommands.Location = new System.Drawing.Point(3, 4);
			this.listBoxSubCommands.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
			this.listBoxSubCommands.Name = "listBoxSubCommands";
			this.listBoxSubCommands.Size = new System.Drawing.Size(389, 254);
			this.listBoxSubCommands.TabIndex = 0;
			// 
			// tabControlObjectsList
			// 
			this.tabControlObjectsList.Controls.Add(this.tabPageTextures);
			this.tabControlObjectsList.Controls.Add(this.tabPagePrograms);
			this.tabControlObjectsList.Controls.Add(this.tabPageVBOs);
			this.tabControlObjectsList.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControlObjectsList.Location = new System.Drawing.Point(0, 0);
			this.tabControlObjectsList.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabControlObjectsList.Name = "tabControlObjectsList";
			this.tabControlObjectsList.SelectedIndex = 0;
			this.tabControlObjectsList.Size = new System.Drawing.Size(340, 672);
			this.tabControlObjectsList.TabIndex = 0;
			// 
			// tabPageTextures
			// 
			this.tabPageTextures.Controls.Add(this.panelTextures);
			this.tabPageTextures.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.tabPageTextures.Location = new System.Drawing.Point(4, 27);
			this.tabPageTextures.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageTextures.Name = "tabPageTextures";
			this.tabPageTextures.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageTextures.Size = new System.Drawing.Size(332, 641);
			this.tabPageTextures.TabIndex = 0;
			this.tabPageTextures.Text = "Textures";
			this.tabPageTextures.UseVisualStyleBackColor = true;
			// 
			// panelTextures
			// 
			this.panelTextures.Controls.Add(this.listViewTextures);
			this.panelTextures.Controls.Add(this.labelTexturesSummary);
			this.panelTextures.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panelTextures.Location = new System.Drawing.Point(3, 4);
			this.panelTextures.Name = "panelTextures";
			this.panelTextures.Size = new System.Drawing.Size(326, 633);
			this.panelTextures.TabIndex = 3;
			this.panelTextures.Visible = false;
			// 
			// listViewTextures
			// 
			this.listViewTextures.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.listViewTextures.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader_TexId,
            this.columnHeader_W,
            this.columnHeader_H,
            this.columnHeader_Format,
            this.columnHeader_Mips,
            this.columnHeader_Bytes,
            this.columnHeader_Pixels,
            this.columnHeader_2n,
            this.columnHeader_Square,
            this.columnHeader_TexType,
            this.columnHeader_TexUnit,
            this.columnHeader_TexInUse});
			this.listViewTextures.FullRowSelect = true;
			this.listViewTextures.GridLines = true;
			this.listViewTextures.Location = new System.Drawing.Point(0, 0);
			this.listViewTextures.MultiSelect = false;
			this.listViewTextures.Name = "listViewTextures";
			this.listViewTextures.ShowGroups = false;
			this.listViewTextures.Size = new System.Drawing.Size(326, 602);
			this.listViewTextures.Sorting = System.Windows.Forms.SortOrder.Ascending;
			this.listViewTextures.TabIndex = 0;
			this.listViewTextures.UseCompatibleStateImageBehavior = false;
			this.listViewTextures.View = System.Windows.Forms.View.Details;
			this.listViewTextures.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.listViewTextures_ColumnClick);
			this.listViewTextures.ItemActivate += new System.EventHandler(this.listViewTextures_ItemActivate);
			// 
			// columnHeader_TexId
			// 
			this.columnHeader_TexId.Text = "Id";
			this.columnHeader_TexId.Width = 53;
			// 
			// columnHeader_W
			// 
			this.columnHeader_W.Text = "W";
			// 
			// columnHeader_H
			// 
			this.columnHeader_H.Text = "H";
			// 
			// columnHeader_Format
			// 
			this.columnHeader_Format.Text = "Format";
			this.columnHeader_Format.Width = 123;
			// 
			// columnHeader_Mips
			// 
			this.columnHeader_Mips.Text = "Mips";
			this.columnHeader_Mips.Width = 40;
			// 
			// columnHeader_Bytes
			// 
			this.columnHeader_Bytes.Text = "Bytes";
			this.columnHeader_Bytes.Width = 83;
			// 
			// columnHeader_Pixels
			// 
			this.columnHeader_Pixels.Text = "Pixels";
			this.columnHeader_Pixels.Width = 88;
			// 
			// columnHeader_2n
			// 
			this.columnHeader_2n.Text = "2^n?";
			this.columnHeader_2n.Width = 50;
			// 
			// columnHeader_Square
			// 
			this.columnHeader_Square.Text = "Square?";
			// 
			// columnHeader_TexType
			// 
			this.columnHeader_TexType.Text = "Type";
			// 
			// columnHeader_TexUnit
			// 
			this.columnHeader_TexUnit.Text = "Unit(s)";
			// 
			// columnHeader_TexInUse
			// 
			this.columnHeader_TexInUse.Text = "In use?";
			// 
			// labelTexturesSummary
			// 
			this.labelTexturesSummary.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.labelTexturesSummary.AutoSize = true;
			this.labelTexturesSummary.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelTexturesSummary.Location = new System.Drawing.Point(8, 611);
			this.labelTexturesSummary.Name = "labelTexturesSummary";
			this.labelTexturesSummary.Size = new System.Drawing.Size(99, 18);
			this.labelTexturesSummary.TabIndex = 2;
			this.labelTexturesSummary.Text = "ZZZZZZZZZZZZZ";
			// 
			// tabPagePrograms
			// 
			this.tabPagePrograms.Controls.Add(this.panelPrograms);
			this.tabPagePrograms.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.tabPagePrograms.Location = new System.Drawing.Point(4, 22);
			this.tabPagePrograms.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPagePrograms.Name = "tabPagePrograms";
			this.tabPagePrograms.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPagePrograms.Size = new System.Drawing.Size(332, 646);
			this.tabPagePrograms.TabIndex = 1;
			this.tabPagePrograms.Text = "Programs";
			this.tabPagePrograms.UseVisualStyleBackColor = true;
			// 
			// panelPrograms
			// 
			this.panelPrograms.Controls.Add(this.labelProgramsSummary);
			this.panelPrograms.Controls.Add(this.listViewPrograms);
			this.panelPrograms.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panelPrograms.Location = new System.Drawing.Point(3, 4);
			this.panelPrograms.Name = "panelPrograms";
			this.panelPrograms.Size = new System.Drawing.Size(326, 638);
			this.panelPrograms.TabIndex = 5;
			this.panelPrograms.Visible = false;
			// 
			// labelProgramsSummary
			// 
			this.labelProgramsSummary.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.labelProgramsSummary.AutoSize = true;
			this.labelProgramsSummary.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelProgramsSummary.Location = new System.Drawing.Point(8, 616);
			this.labelProgramsSummary.Name = "labelProgramsSummary";
			this.labelProgramsSummary.Size = new System.Drawing.Size(99, 18);
			this.labelProgramsSummary.TabIndex = 4;
			this.labelProgramsSummary.Text = "ZZZZZZZZZZZZZ";
			// 
			// listViewPrograms
			// 
			this.listViewPrograms.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.listViewPrograms.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader_ProgId,
            this.columnHeader_VS,
            this.columnHeader_FS});
			this.listViewPrograms.FullRowSelect = true;
			this.listViewPrograms.GridLines = true;
			this.listViewPrograms.Location = new System.Drawing.Point(0, 0);
			this.listViewPrograms.MultiSelect = false;
			this.listViewPrograms.Name = "listViewPrograms";
			this.listViewPrograms.ShowGroups = false;
			this.listViewPrograms.Size = new System.Drawing.Size(326, 607);
			this.listViewPrograms.Sorting = System.Windows.Forms.SortOrder.Ascending;
			this.listViewPrograms.TabIndex = 2;
			this.listViewPrograms.UseCompatibleStateImageBehavior = false;
			this.listViewPrograms.View = System.Windows.Forms.View.Details;
			this.listViewPrograms.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.listViewPrograms_ColumnClick);
			this.listViewPrograms.ItemActivate += new System.EventHandler(this.listViewPrograms_ItemActivate);
			// 
			// columnHeader_ProgId
			// 
			this.columnHeader_ProgId.Text = "Id";
			this.columnHeader_ProgId.Width = 88;
			// 
			// columnHeader_VS
			// 
			this.columnHeader_VS.Text = "VS";
			this.columnHeader_VS.Width = 90;
			// 
			// columnHeader_FS
			// 
			this.columnHeader_FS.Text = "FS";
			this.columnHeader_FS.Width = 95;
			// 
			// tabPageVBOs
			// 
			this.tabPageVBOs.Controls.Add(this.panelVbos);
			this.tabPageVBOs.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.tabPageVBOs.Location = new System.Drawing.Point(4, 22);
			this.tabPageVBOs.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageVBOs.Name = "tabPageVBOs";
			this.tabPageVBOs.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageVBOs.Size = new System.Drawing.Size(332, 646);
			this.tabPageVBOs.TabIndex = 2;
			this.tabPageVBOs.Text = "VBOs";
			this.tabPageVBOs.UseVisualStyleBackColor = true;
			// 
			// panelVbos
			// 
			this.panelVbos.Controls.Add(this.labelVbosSummary);
			this.panelVbos.Controls.Add(this.listViewVbos);
			this.panelVbos.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panelVbos.Location = new System.Drawing.Point(3, 4);
			this.panelVbos.Name = "panelVbos";
			this.panelVbos.Size = new System.Drawing.Size(326, 638);
			this.panelVbos.TabIndex = 4;
			this.panelVbos.Visible = false;
			// 
			// labelVbosSummary
			// 
			this.labelVbosSummary.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.labelVbosSummary.AutoSize = true;
			this.labelVbosSummary.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelVbosSummary.Location = new System.Drawing.Point(8, 616);
			this.labelVbosSummary.Name = "labelVbosSummary";
			this.labelVbosSummary.Size = new System.Drawing.Size(99, 18);
			this.labelVbosSummary.TabIndex = 5;
			this.labelVbosSummary.Text = "ZZZZZZZZZZZZZ";
			// 
			// listViewVbos
			// 
			this.listViewVbos.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.listViewVbos.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader_VboId,
            this.columnHeader_Size,
            this.columnHeader_Usage,
            this.columnHeader_VboInUse});
			this.listViewVbos.FullRowSelect = true;
			this.listViewVbos.GridLines = true;
			this.listViewVbos.Location = new System.Drawing.Point(0, 0);
			this.listViewVbos.MultiSelect = false;
			this.listViewVbos.Name = "listViewVbos";
			this.listViewVbos.ShowGroups = false;
			this.listViewVbos.Size = new System.Drawing.Size(326, 607);
			this.listViewVbos.Sorting = System.Windows.Forms.SortOrder.Ascending;
			this.listViewVbos.TabIndex = 3;
			this.listViewVbos.UseCompatibleStateImageBehavior = false;
			this.listViewVbos.View = System.Windows.Forms.View.Details;
			this.listViewVbos.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.listViewVbos_ColumnClick);
			this.listViewVbos.ItemActivate += new System.EventHandler(this.listViewVbos_ItemActivate);
			// 
			// columnHeader_VboId
			// 
			this.columnHeader_VboId.Text = "Id";
			// 
			// columnHeader_Size
			// 
			this.columnHeader_Size.Text = "Size";
			// 
			// columnHeader_Usage
			// 
			this.columnHeader_Usage.Text = "Usage";
			this.columnHeader_Usage.Width = 160;
			// 
			// columnHeader_VboInUse
			// 
			this.columnHeader_VboInUse.Text = "In use?";
			// 
			// panelScreenShot
			// 
			this.panelScreenShot.AutoScroll = true;
			this.panelScreenShot.Controls.Add(this.pictureBoxScreenShot);
			this.panelScreenShot.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panelScreenShot.Location = new System.Drawing.Point(0, 0);
			this.panelScreenShot.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.panelScreenShot.Name = "panelScreenShot";
			this.panelScreenShot.Size = new System.Drawing.Size(796, 336);
			this.panelScreenShot.TabIndex = 0;
			// 
			// pictureBoxScreenShot
			// 
			this.pictureBoxScreenShot.BackColor = System.Drawing.SystemColors.Control;
			this.pictureBoxScreenShot.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pictureBoxScreenShot.Dock = System.Windows.Forms.DockStyle.Fill;
			this.pictureBoxScreenShot.Location = new System.Drawing.Point(0, 0);
			this.pictureBoxScreenShot.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.pictureBoxScreenShot.Name = "pictureBoxScreenShot";
			this.pictureBoxScreenShot.Size = new System.Drawing.Size(796, 336);
			this.pictureBoxScreenShot.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.pictureBoxScreenShot.TabIndex = 9;
			this.pictureBoxScreenShot.TabStop = false;
			this.pictureBoxScreenShot.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBoxScreenShot_MouseClick);
			// 
			// splitContainerLeft
			// 
			this.splitContainerLeft.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.splitContainerLeft.Location = new System.Drawing.Point(5, 38);
			this.splitContainerLeft.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.splitContainerLeft.Name = "splitContainerLeft";
			this.splitContainerLeft.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// splitContainerLeft.Panel1
			// 
			this.splitContainerLeft.Panel1.Controls.Add(this.panelScreenShot);
			// 
			// splitContainerLeft.Panel2
			// 
			this.splitContainerLeft.Panel2.Controls.Add(this.splitContainerOpenGLCalls);
			this.splitContainerLeft.Size = new System.Drawing.Size(796, 634);
			this.splitContainerLeft.SplitterDistance = 336;
			this.splitContainerLeft.SplitterWidth = 5;
			this.splitContainerLeft.TabIndex = 11;
			// 
			// splitContainerOpenGLCalls
			// 
			this.splitContainerOpenGLCalls.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainerOpenGLCalls.Location = new System.Drawing.Point(0, 0);
			this.splitContainerOpenGLCalls.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.splitContainerOpenGLCalls.Name = "splitContainerOpenGLCalls";
			// 
			// splitContainerOpenGLCalls.Panel1
			// 
			this.splitContainerOpenGLCalls.Panel1.Controls.Add(this.tabControlRenderCalls);
			// 
			// splitContainerOpenGLCalls.Panel2
			// 
			this.splitContainerOpenGLCalls.Panel2.Controls.Add(this.tabControl_API_Calls);
			this.splitContainerOpenGLCalls.Size = new System.Drawing.Size(796, 293);
			this.splitContainerOpenGLCalls.SplitterDistance = 388;
			this.splitContainerOpenGLCalls.SplitterWidth = 5;
			this.splitContainerOpenGLCalls.TabIndex = 0;
			// 
			// tabControlRenderCalls
			// 
			this.tabControlRenderCalls.Controls.Add(this.tabPageRenderCalls);
			this.tabControlRenderCalls.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControlRenderCalls.Location = new System.Drawing.Point(0, 0);
			this.tabControlRenderCalls.Name = "tabControlRenderCalls";
			this.tabControlRenderCalls.SelectedIndex = 0;
			this.tabControlRenderCalls.Size = new System.Drawing.Size(388, 293);
			this.tabControlRenderCalls.TabIndex = 0;
			// 
			// tabPageRenderCalls
			// 
			this.tabPageRenderCalls.Controls.Add(this.listBoxRenderCommands);
			this.tabPageRenderCalls.Location = new System.Drawing.Point(4, 27);
			this.tabPageRenderCalls.Name = "tabPageRenderCalls";
			this.tabPageRenderCalls.Padding = new System.Windows.Forms.Padding(3);
			this.tabPageRenderCalls.Size = new System.Drawing.Size(380, 262);
			this.tabPageRenderCalls.TabIndex = 0;
			this.tabPageRenderCalls.Text = "Render calls";
			this.tabPageRenderCalls.UseVisualStyleBackColor = true;
			// 
			// tabControl_API_Calls
			// 
			this.tabControl_API_Calls.Controls.Add(this.tabPageAPICalls);
			this.tabControl_API_Calls.Controls.Add(this.tabPageVertexData);
			this.tabControl_API_Calls.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl_API_Calls.Location = new System.Drawing.Point(0, 0);
			this.tabControl_API_Calls.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabControl_API_Calls.Name = "tabControl_API_Calls";
			this.tabControl_API_Calls.SelectedIndex = 0;
			this.tabControl_API_Calls.Size = new System.Drawing.Size(403, 293);
			this.tabControl_API_Calls.TabIndex = 0;
			// 
			// tabPageAPICalls
			// 
			this.tabPageAPICalls.Controls.Add(this.listBoxSubCommands);
			this.tabPageAPICalls.Location = new System.Drawing.Point(4, 27);
			this.tabPageAPICalls.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageAPICalls.Name = "tabPageAPICalls";
			this.tabPageAPICalls.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageAPICalls.Size = new System.Drawing.Size(395, 262);
			this.tabPageAPICalls.TabIndex = 0;
			this.tabPageAPICalls.Text = "API calls";
			this.tabPageAPICalls.UseVisualStyleBackColor = true;
			// 
			// tabPageVertexData
			// 
			this.tabPageVertexData.Location = new System.Drawing.Point(4, 22);
			this.tabPageVertexData.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageVertexData.Name = "tabPageVertexData";
			this.tabPageVertexData.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageVertexData.Size = new System.Drawing.Size(395, 267);
			this.tabPageVertexData.TabIndex = 1;
			this.tabPageVertexData.Text = "Vertex data";
			this.tabPageVertexData.UseVisualStyleBackColor = true;
			// 
			// splitContainerMaster
			// 
			this.splitContainerMaster.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.splitContainerMaster.Location = new System.Drawing.Point(2, 5);
			this.splitContainerMaster.Name = "splitContainerMaster";
			// 
			// splitContainerMaster.Panel1
			// 
			this.splitContainerMaster.Panel1.Controls.Add(this.checkBoxScaleSS);
			this.splitContainerMaster.Panel1.Controls.Add(this.textBoxPort);
			this.splitContainerMaster.Panel1.Controls.Add(this.label2);
			this.splitContainerMaster.Panel1.Controls.Add(this.textBoxServer);
			this.splitContainerMaster.Panel1.Controls.Add(this.label1);
			this.splitContainerMaster.Panel1.Controls.Add(this.comboBoxZoomSS);
			this.splitContainerMaster.Panel1.Controls.Add(this.comboBoxPlatform);
			this.splitContainerMaster.Panel1.Controls.Add(this.splitContainerLeft);
			this.splitContainerMaster.Panel1.Controls.Add(this.buttonCapture);
			// 
			// splitContainerMaster.Panel2
			// 
			this.splitContainerMaster.Panel2.Controls.Add(this.tabControlObjectsList);
			this.splitContainerMaster.Size = new System.Drawing.Size(1147, 672);
			this.splitContainerMaster.SplitterDistance = 803;
			this.splitContainerMaster.TabIndex = 16;
			// 
			// checkBoxScaleSS
			// 
			this.checkBoxScaleSS.AutoSize = true;
			this.checkBoxScaleSS.Checked = true;
			this.checkBoxScaleSS.CheckState = System.Windows.Forms.CheckState.Checked;
			this.checkBoxScaleSS.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.checkBoxScaleSS.Location = new System.Drawing.Point(598, 7);
			this.checkBoxScaleSS.Name = "checkBoxScaleSS";
			this.checkBoxScaleSS.Size = new System.Drawing.Size(137, 22);
			this.checkBoxScaleSS.TabIndex = 16;
			this.checkBoxScaleSS.Text = "Scale screenshot?";
			this.checkBoxScaleSS.UseVisualStyleBackColor = true;
			// 
			// textBoxPort
			// 
			this.textBoxPort.Location = new System.Drawing.Point(528, 5);
			this.textBoxPort.Name = "textBoxPort";
			this.textBoxPort.Size = new System.Drawing.Size(53, 26);
			this.textBoxPort.TabIndex = 15;
			this.textBoxPort.Text = "38301";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label2.Location = new System.Drawing.Point(492, 8);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(34, 18);
			this.label2.TabIndex = 14;
			this.label2.Text = "Port";
			// 
			// textBoxServer
			// 
			this.textBoxServer.Location = new System.Drawing.Point(374, 5);
			this.textBoxServer.Name = "textBoxServer";
			this.textBoxServer.Size = new System.Drawing.Size(110, 26);
			this.textBoxServer.TabIndex = 13;
			this.textBoxServer.Text = "127.0.0.1";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(324, 8);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(48, 18);
			this.label1.TabIndex = 12;
			this.label1.Text = "Server";
			// 
			// comboBoxZoomSS
			// 
			this.comboBoxZoomSS.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboBoxZoomSS.FormattingEnabled = true;
			this.comboBoxZoomSS.Items.AddRange(new object[] {
            "100 %",
            "50 %",
            "25 %"});
			this.comboBoxZoomSS.Location = new System.Drawing.Point(216, 4);
			this.comboBoxZoomSS.Name = "comboBoxZoomSS";
			this.comboBoxZoomSS.Size = new System.Drawing.Size(96, 26);
			this.comboBoxZoomSS.TabIndex = 2;
			this.comboBoxZoomSS.SelectedIndexChanged += new System.EventHandler(this.comboBoxZoomSS_SelectedIndexChanged);
			// 
			// comboBoxPlatform
			// 
			this.comboBoxPlatform.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboBoxPlatform.FormattingEnabled = true;
			this.comboBoxPlatform.Items.AddRange(new object[] {
            "Android",
            "Tizen",
            "Win32"});
			this.comboBoxPlatform.Location = new System.Drawing.Point(114, 4);
			this.comboBoxPlatform.Name = "comboBoxPlatform";
			this.comboBoxPlatform.Size = new System.Drawing.Size(96, 26);
			this.comboBoxPlatform.TabIndex = 1;
			this.comboBoxPlatform.SelectedIndexChanged += new System.EventHandler(this.comboBoxPlatform_SelectedIndexChanged);
			// 
			// FormMain
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 18F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1153, 682);
			this.Controls.Add(this.splitContainerMaster);
			this.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
			this.Name = "FormMain";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "KataProfiler 2.3 © nghia.buivan@gameloft.com";
			this.Load += new System.EventHandler(this.FormMain_Load);
			this.tabControlObjectsList.ResumeLayout(false);
			this.tabPageTextures.ResumeLayout(false);
			this.panelTextures.ResumeLayout(false);
			this.panelTextures.PerformLayout();
			this.tabPagePrograms.ResumeLayout(false);
			this.panelPrograms.ResumeLayout(false);
			this.panelPrograms.PerformLayout();
			this.tabPageVBOs.ResumeLayout(false);
			this.panelVbos.ResumeLayout(false);
			this.panelVbos.PerformLayout();
			this.panelScreenShot.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.pictureBoxScreenShot)).EndInit();
			this.splitContainerLeft.Panel1.ResumeLayout(false);
			this.splitContainerLeft.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainerLeft)).EndInit();
			this.splitContainerLeft.ResumeLayout(false);
			this.splitContainerOpenGLCalls.Panel1.ResumeLayout(false);
			this.splitContainerOpenGLCalls.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainerOpenGLCalls)).EndInit();
			this.splitContainerOpenGLCalls.ResumeLayout(false);
			this.tabControlRenderCalls.ResumeLayout(false);
			this.tabPageRenderCalls.ResumeLayout(false);
			this.tabControl_API_Calls.ResumeLayout(false);
			this.tabPageAPICalls.ResumeLayout(false);
			this.splitContainerMaster.Panel1.ResumeLayout(false);
			this.splitContainerMaster.Panel1.PerformLayout();
			this.splitContainerMaster.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainerMaster)).EndInit();
			this.splitContainerMaster.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button buttonCapture;
		private System.Windows.Forms.ListBox listBoxRenderCommands;
		private System.Windows.Forms.ListBox listBoxSubCommands;
		private System.Windows.Forms.TabControl tabControlObjectsList;
		private System.Windows.Forms.TabPage tabPageTextures;
		private System.Windows.Forms.TabPage tabPagePrograms;
		private System.Windows.Forms.PictureBox pictureBoxScreenShot;
		private System.Windows.Forms.Panel panelScreenShot;
		private System.Windows.Forms.SplitContainer splitContainerLeft;
		private System.Windows.Forms.SplitContainer splitContainerOpenGLCalls;
		private System.Windows.Forms.TabPage tabPageVBOs;
		private System.Windows.Forms.TabControl tabControl_API_Calls;
		private System.Windows.Forms.TabPage tabPageAPICalls;
		private System.Windows.Forms.TabPage tabPageVertexData;
		private System.Windows.Forms.TabControl tabControlRenderCalls;
		private System.Windows.Forms.TabPage tabPageRenderCalls;
		private System.Windows.Forms.ListView listViewTextures;
		private System.Windows.Forms.ColumnHeader columnHeader_TexId;
		private System.Windows.Forms.ColumnHeader columnHeader_W;
		private System.Windows.Forms.ColumnHeader columnHeader_H;
		private System.Windows.Forms.ColumnHeader columnHeader_Format;
		private System.Windows.Forms.ColumnHeader columnHeader_Bytes;
		private System.Windows.Forms.ColumnHeader columnHeader_Pixels;
		private System.Windows.Forms.ListView listViewPrograms;
		private System.Windows.Forms.ColumnHeader columnHeader_ProgId;
		private System.Windows.Forms.ColumnHeader columnHeader_VS;
		private System.Windows.Forms.ColumnHeader columnHeader_FS;
		private System.Windows.Forms.ListView listViewVbos;
		private System.Windows.Forms.ColumnHeader columnHeader_VboId;
		private System.Windows.Forms.ColumnHeader columnHeader_Size;
		private System.Windows.Forms.ColumnHeader columnHeader_Usage;
		private System.Windows.Forms.Label labelTexturesSummary;
		private System.Windows.Forms.Panel panelTextures;
		private System.Windows.Forms.ColumnHeader columnHeader_TexInUse;
		private System.Windows.Forms.ColumnHeader columnHeader_VboInUse;
		private System.Windows.Forms.Label labelProgramsSummary;
		private System.Windows.Forms.Panel panelPrograms;
		private System.Windows.Forms.Panel panelVbos;
		private System.Windows.Forms.Label labelVbosSummary;
		private System.Windows.Forms.ColumnHeader columnHeader_2n;
		private System.Windows.Forms.SplitContainer splitContainerMaster;
		private System.Windows.Forms.ColumnHeader columnHeader_Mips;
		private System.Windows.Forms.ColumnHeader columnHeader_Square;
		private System.Windows.Forms.ColumnHeader columnHeader_TexUnit;
		private System.Windows.Forms.ComboBox comboBoxZoomSS;
		private System.Windows.Forms.ComboBox comboBoxPlatform;
		private System.Windows.Forms.ColumnHeader columnHeader_TexType;
		private System.Windows.Forms.TextBox textBoxPort;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textBoxServer;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.CheckBox checkBoxScaleSS;
	}
}

