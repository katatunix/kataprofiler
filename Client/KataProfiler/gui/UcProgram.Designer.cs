namespace KataProfiler
{
	partial class UcProgram
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

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.tabControl = new System.Windows.Forms.TabControl();
			this.tabPageVS = new System.Windows.Forms.TabPage();
			this.fastColoredTextBoxVS = new FastColoredTextBoxNS.FastColoredTextBox();
			this.tabPageFS = new System.Windows.Forms.TabPage();
			this.fastColoredTextBoxFS = new FastColoredTextBoxNS.FastColoredTextBox();
			this.richTextBoxATT = new System.Windows.Forms.RichTextBox();
			this.labelATT = new System.Windows.Forms.Label();
			this.labelUNI = new System.Windows.Forms.Label();
			this.richTextBoxUNI = new System.Windows.Forms.RichTextBox();
			this.buttonSend = new System.Windows.Forms.Button();
			this.splitContainerMaster = new System.Windows.Forms.SplitContainer();
			this.splitContainerRight = new System.Windows.Forms.SplitContainer();
			this.buttonRevert = new System.Windows.Forms.Button();
			this.buttonRevertAll = new System.Windows.Forms.Button();
			this.fastColoredTextBoxOutput = new FastColoredTextBoxNS.FastColoredTextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.tabPage1 = new System.Windows.Forms.TabPage();
			this.richTextBox1 = new System.Windows.Forms.RichTextBox();
			this.tabControl.SuspendLayout();
			this.tabPageVS.SuspendLayout();
			this.tabPageFS.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainerMaster)).BeginInit();
			this.splitContainerMaster.Panel1.SuspendLayout();
			this.splitContainerMaster.Panel2.SuspendLayout();
			this.splitContainerMaster.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainerRight)).BeginInit();
			this.splitContainerRight.Panel1.SuspendLayout();
			this.splitContainerRight.Panel2.SuspendLayout();
			this.splitContainerRight.SuspendLayout();
			this.tabPage1.SuspendLayout();
			this.SuspendLayout();
			// 
			// tabControl
			// 
			this.tabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.tabControl.Controls.Add(this.tabPageVS);
			this.tabControl.Controls.Add(this.tabPageFS);
			this.tabControl.Controls.Add(this.tabPage1);
			this.tabControl.Location = new System.Drawing.Point(0, 8);
			this.tabControl.Margin = new System.Windows.Forms.Padding(4);
			this.tabControl.Name = "tabControl";
			this.tabControl.SelectedIndex = 0;
			this.tabControl.Size = new System.Drawing.Size(604, 408);
			this.tabControl.TabIndex = 0;
			// 
			// tabPageVS
			// 
			this.tabPageVS.Controls.Add(this.fastColoredTextBoxVS);
			this.tabPageVS.Location = new System.Drawing.Point(4, 27);
			this.tabPageVS.Margin = new System.Windows.Forms.Padding(4);
			this.tabPageVS.Name = "tabPageVS";
			this.tabPageVS.Padding = new System.Windows.Forms.Padding(4);
			this.tabPageVS.Size = new System.Drawing.Size(596, 377);
			this.tabPageVS.TabIndex = 0;
			this.tabPageVS.Text = "VS";
			this.tabPageVS.UseVisualStyleBackColor = true;
			// 
			// fastColoredTextBoxVS
			// 
			this.fastColoredTextBoxVS.AllowDrop = true;
			this.fastColoredTextBoxVS.AutoScrollMinSize = new System.Drawing.Size(25, 15);
			this.fastColoredTextBoxVS.BackBrush = null;
			this.fastColoredTextBoxVS.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.fastColoredTextBoxVS.DisabledColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))));
			this.fastColoredTextBoxVS.Dock = System.Windows.Forms.DockStyle.Fill;
			this.fastColoredTextBoxVS.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.fastColoredTextBoxVS.IsReplaceMode = false;
			this.fastColoredTextBoxVS.Language = FastColoredTextBoxNS.Language.CSharp;
			this.fastColoredTextBoxVS.Location = new System.Drawing.Point(4, 4);
			this.fastColoredTextBoxVS.Name = "fastColoredTextBoxVS";
			this.fastColoredTextBoxVS.Paddings = new System.Windows.Forms.Padding(0);
			this.fastColoredTextBoxVS.SelectionColor = System.Drawing.Color.FromArgb(((int)(((byte)(50)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(255)))));
			this.fastColoredTextBoxVS.Size = new System.Drawing.Size(588, 369);
			this.fastColoredTextBoxVS.TabIndex = 0;
			// 
			// tabPageFS
			// 
			this.tabPageFS.Controls.Add(this.fastColoredTextBoxFS);
			this.tabPageFS.Location = new System.Drawing.Point(4, 22);
			this.tabPageFS.Margin = new System.Windows.Forms.Padding(4);
			this.tabPageFS.Name = "tabPageFS";
			this.tabPageFS.Padding = new System.Windows.Forms.Padding(4);
			this.tabPageFS.Size = new System.Drawing.Size(596, 374);
			this.tabPageFS.TabIndex = 1;
			this.tabPageFS.Text = "FS";
			this.tabPageFS.UseVisualStyleBackColor = true;
			// 
			// fastColoredTextBoxFS
			// 
			this.fastColoredTextBoxFS.AllowDrop = true;
			this.fastColoredTextBoxFS.AutoScrollMinSize = new System.Drawing.Size(25, 15);
			this.fastColoredTextBoxFS.BackBrush = null;
			this.fastColoredTextBoxFS.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.fastColoredTextBoxFS.DisabledColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))));
			this.fastColoredTextBoxFS.Dock = System.Windows.Forms.DockStyle.Fill;
			this.fastColoredTextBoxFS.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.fastColoredTextBoxFS.IsReplaceMode = false;
			this.fastColoredTextBoxFS.Language = FastColoredTextBoxNS.Language.CSharp;
			this.fastColoredTextBoxFS.Location = new System.Drawing.Point(4, 4);
			this.fastColoredTextBoxFS.Name = "fastColoredTextBoxFS";
			this.fastColoredTextBoxFS.Paddings = new System.Windows.Forms.Padding(0);
			this.fastColoredTextBoxFS.SelectionColor = System.Drawing.Color.FromArgb(((int)(((byte)(50)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(255)))));
			this.fastColoredTextBoxFS.Size = new System.Drawing.Size(588, 366);
			this.fastColoredTextBoxFS.TabIndex = 1;
			// 
			// richTextBoxATT
			// 
			this.richTextBoxATT.Anchor = System.Windows.Forms.AnchorStyles.Left;
			this.richTextBoxATT.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.richTextBoxATT.Location = new System.Drawing.Point(10, 32);
			this.richTextBoxATT.Name = "richTextBoxATT";
			this.richTextBoxATT.ReadOnly = true;
			this.richTextBoxATT.Size = new System.Drawing.Size(218, 234);
			this.richTextBoxATT.TabIndex = 1;
			this.richTextBoxATT.Text = "";
			// 
			// labelATT
			// 
			this.labelATT.AutoSize = true;
			this.labelATT.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelATT.Location = new System.Drawing.Point(10, 6);
			this.labelATT.Name = "labelATT";
			this.labelATT.Size = new System.Drawing.Size(111, 18);
			this.labelATT.TabIndex = 2;
			this.labelATT.Text = "Active attributes";
			// 
			// labelUNI
			// 
			this.labelUNI.AutoSize = true;
			this.labelUNI.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelUNI.Location = new System.Drawing.Point(10, 276);
			this.labelUNI.Name = "labelUNI";
			this.labelUNI.Size = new System.Drawing.Size(106, 18);
			this.labelUNI.TabIndex = 4;
			this.labelUNI.Text = "Active uniforms";
			// 
			// richTextBoxUNI
			// 
			this.richTextBoxUNI.Anchor = System.Windows.Forms.AnchorStyles.Left;
			this.richTextBoxUNI.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.richTextBoxUNI.Location = new System.Drawing.Point(10, 304);
			this.richTextBoxUNI.Name = "richTextBoxUNI";
			this.richTextBoxUNI.ReadOnly = true;
			this.richTextBoxUNI.Size = new System.Drawing.Size(218, 234);
			this.richTextBoxUNI.TabIndex = 3;
			this.richTextBoxUNI.Text = "";
			// 
			// buttonSend
			// 
			this.buttonSend.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.buttonSend.Location = new System.Drawing.Point(185, 0);
			this.buttonSend.Name = "buttonSend";
			this.buttonSend.Size = new System.Drawing.Size(75, 26);
			this.buttonSend.TabIndex = 5;
			this.buttonSend.Text = "&Send";
			this.buttonSend.UseVisualStyleBackColor = true;
			this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
			// 
			// splitContainerMaster
			// 
			this.splitContainerMaster.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainerMaster.Location = new System.Drawing.Point(0, 0);
			this.splitContainerMaster.Name = "splitContainerMaster";
			// 
			// splitContainerMaster.Panel1
			// 
			this.splitContainerMaster.Panel1.Controls.Add(this.richTextBoxATT);
			this.splitContainerMaster.Panel1.Controls.Add(this.labelATT);
			this.splitContainerMaster.Panel1.Controls.Add(this.labelUNI);
			this.splitContainerMaster.Panel1.Controls.Add(this.richTextBoxUNI);
			this.splitContainerMaster.Panel1.SizeChanged += new System.EventHandler(this.splitContainer1_Panel1_SizeChanged);
			// 
			// splitContainerMaster.Panel2
			// 
			this.splitContainerMaster.Panel2.Controls.Add(this.splitContainerRight);
			this.splitContainerMaster.Size = new System.Drawing.Size(856, 554);
			this.splitContainerMaster.SplitterDistance = 241;
			this.splitContainerMaster.TabIndex = 6;
			// 
			// splitContainerRight
			// 
			this.splitContainerRight.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainerRight.Location = new System.Drawing.Point(0, 0);
			this.splitContainerRight.Name = "splitContainerRight";
			this.splitContainerRight.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// splitContainerRight.Panel1
			// 
			this.splitContainerRight.Panel1.Controls.Add(this.tabControl);
			// 
			// splitContainerRight.Panel2
			// 
			this.splitContainerRight.Panel2.Controls.Add(this.label1);
			this.splitContainerRight.Panel2.Controls.Add(this.buttonSend);
			this.splitContainerRight.Panel2.Controls.Add(this.fastColoredTextBoxOutput);
			this.splitContainerRight.Panel2.Controls.Add(this.buttonRevert);
			this.splitContainerRight.Panel2.Controls.Add(this.buttonRevertAll);
			this.splitContainerRight.Size = new System.Drawing.Size(611, 554);
			this.splitContainerRight.SplitterDistance = 418;
			this.splitContainerRight.TabIndex = 0;
			// 
			// buttonRevert
			// 
			this.buttonRevert.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.buttonRevert.Location = new System.Drawing.Point(-1, 0);
			this.buttonRevert.Name = "buttonRevert";
			this.buttonRevert.Size = new System.Drawing.Size(75, 26);
			this.buttonRevert.TabIndex = 8;
			this.buttonRevert.Text = "&Revert";
			this.buttonRevert.UseVisualStyleBackColor = true;
			this.buttonRevert.Click += new System.EventHandler(this.buttonRevert_Click);
			// 
			// buttonRevertAll
			// 
			this.buttonRevertAll.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.buttonRevertAll.Location = new System.Drawing.Point(81, 0);
			this.buttonRevertAll.Name = "buttonRevertAll";
			this.buttonRevertAll.Size = new System.Drawing.Size(75, 26);
			this.buttonRevertAll.TabIndex = 7;
			this.buttonRevertAll.Text = "Revert &all";
			this.buttonRevertAll.UseVisualStyleBackColor = true;
			this.buttonRevertAll.Click += new System.EventHandler(this.buttonRevertAll_Click);
			// 
			// fastColoredTextBoxOutput
			// 
			this.fastColoredTextBoxOutput.AllowDrop = true;
			this.fastColoredTextBoxOutput.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.fastColoredTextBoxOutput.AutoScrollMinSize = new System.Drawing.Size(67, 15);
			this.fastColoredTextBoxOutput.BackBrush = null;
			this.fastColoredTextBoxOutput.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.fastColoredTextBoxOutput.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.fastColoredTextBoxOutput.DisabledColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))));
			this.fastColoredTextBoxOutput.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.fastColoredTextBoxOutput.IsReplaceMode = false;
			this.fastColoredTextBoxOutput.Language = FastColoredTextBoxNS.Language.CSharp;
			this.fastColoredTextBoxOutput.LeftBracket = '(';
			this.fastColoredTextBoxOutput.Location = new System.Drawing.Point(-1, 34);
			this.fastColoredTextBoxOutput.Name = "fastColoredTextBoxOutput";
			this.fastColoredTextBoxOutput.Paddings = new System.Windows.Forms.Padding(0);
			this.fastColoredTextBoxOutput.ReadOnly = true;
			this.fastColoredTextBoxOutput.RightBracket = ')';
			this.fastColoredTextBoxOutput.SelectionColor = System.Drawing.Color.FromArgb(((int)(((byte)(50)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(255)))));
			this.fastColoredTextBoxOutput.Size = new System.Drawing.Size(604, 90);
			this.fastColoredTextBoxOutput.TabIndex = 1;
			this.fastColoredTextBoxOutput.Text = "Output";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(325, 4);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(211, 18);
			this.label1.TabIndex = 9;
			this.label1.Text = "Shortcut keys: Alt+R, Alt+A, Alt+S";
			// 
			// tabPage1
			// 
			this.tabPage1.Controls.Add(this.richTextBox1);
			this.tabPage1.Location = new System.Drawing.Point(4, 27);
			this.tabPage1.Name = "tabPage1";
			this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
			this.tabPage1.Size = new System.Drawing.Size(596, 377);
			this.tabPage1.TabIndex = 2;
			this.tabPage1.Text = "Snippets";
			this.tabPage1.UseVisualStyleBackColor = true;
			// 
			// richTextBox1
			// 
			this.richTextBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.richTextBox1.Location = new System.Drawing.Point(3, 3);
			this.richTextBox1.Name = "richTextBox1";
			this.richTextBox1.ReadOnly = true;
			this.richTextBox1.Size = new System.Drawing.Size(590, 371);
			this.richTextBox1.TabIndex = 0;
			this.richTextBox1.Text = "gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n#define lowp highp\n#define mediump highp" +
				"";
			// 
			// UCProgram
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 18F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.splitContainerMaster);
			this.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Margin = new System.Windows.Forms.Padding(4);
			this.MinimumSize = new System.Drawing.Size(650, 300);
			this.Name = "UCProgram";
			this.Size = new System.Drawing.Size(856, 554);
			this.tabControl.ResumeLayout(false);
			this.tabPageVS.ResumeLayout(false);
			this.tabPageFS.ResumeLayout(false);
			this.splitContainerMaster.Panel1.ResumeLayout(false);
			this.splitContainerMaster.Panel1.PerformLayout();
			this.splitContainerMaster.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainerMaster)).EndInit();
			this.splitContainerMaster.ResumeLayout(false);
			this.splitContainerRight.Panel1.ResumeLayout(false);
			this.splitContainerRight.Panel2.ResumeLayout(false);
			this.splitContainerRight.Panel2.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainerRight)).EndInit();
			this.splitContainerRight.ResumeLayout(false);
			this.tabPage1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TabControl tabControl;
		private System.Windows.Forms.TabPage tabPageVS;
		private System.Windows.Forms.TabPage tabPageFS;
		private System.Windows.Forms.RichTextBox richTextBoxATT;
		private System.Windows.Forms.Label labelATT;
		private System.Windows.Forms.Label labelUNI;
		private System.Windows.Forms.RichTextBox richTextBoxUNI;
		private FastColoredTextBoxNS.FastColoredTextBox fastColoredTextBoxVS;
		private FastColoredTextBoxNS.FastColoredTextBox fastColoredTextBoxFS;
		private System.Windows.Forms.Button buttonSend;
		private System.Windows.Forms.SplitContainer splitContainerMaster;
		private System.Windows.Forms.SplitContainer splitContainerRight;
		private FastColoredTextBoxNS.FastColoredTextBox fastColoredTextBoxOutput;
		private System.Windows.Forms.Button buttonRevert;
		private System.Windows.Forms.Button buttonRevertAll;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TabPage tabPage1;
		private System.Windows.Forms.RichTextBox richTextBox1;

	}
}
