namespace KataProfiler
{
	partial class UcTexture
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
			this.pictureBox = new System.Windows.Forms.PictureBox();
			this.listBoxMipmaps = new System.Windows.Forms.ListBox();
			this.label1 = new System.Windows.Forms.Label();
			this.labelSize = new System.Windows.Forms.Label();
			this.labelFormat = new System.Windows.Forms.Label();
			this.labelLength = new System.Windows.Forms.Label();
			this.labelFormat__ = new System.Windows.Forms.Label();
			this.labelLength__ = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.panelTexture = new System.Windows.Forms.Panel();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
			this.panelTexture.SuspendLayout();
			this.SuspendLayout();
			// 
			// pictureBox
			// 
			this.pictureBox.BackColor = System.Drawing.Color.Magenta;
			this.pictureBox.Location = new System.Drawing.Point(0, 0);
			this.pictureBox.Margin = new System.Windows.Forms.Padding(0);
			this.pictureBox.Name = "pictureBox";
			this.pictureBox.Size = new System.Drawing.Size(274, 224);
			this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.pictureBox.TabIndex = 0;
			this.pictureBox.TabStop = false;
			this.pictureBox.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseClick);
			this.pictureBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseMove);
			// 
			// listBoxMipmaps
			// 
			this.listBoxMipmaps.FormattingEnabled = true;
			this.listBoxMipmaps.ItemHeight = 18;
			this.listBoxMipmaps.Location = new System.Drawing.Point(6, 32);
			this.listBoxMipmaps.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
			this.listBoxMipmaps.Name = "listBoxMipmaps";
			this.listBoxMipmaps.Size = new System.Drawing.Size(90, 328);
			this.listBoxMipmaps.TabIndex = 1;
			this.listBoxMipmaps.SelectedIndexChanged += new System.EventHandler(this.listBoxMipmaps_SelectedIndexChanged);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(3, 7);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(72, 19);
			this.label1.TabIndex = 2;
			this.label1.Text = "Mipmaps";
			// 
			// labelSize
			// 
			this.labelSize.AutoSize = true;
			this.labelSize.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelSize.Location = new System.Drawing.Point(142, 8);
			this.labelSize.Name = "labelSize";
			this.labelSize.Size = new System.Drawing.Size(85, 18);
			this.labelSize.TabIndex = 4;
			this.labelSize.Text = "ZZZZZZZZZZZ";
			// 
			// labelFormat
			// 
			this.labelFormat.AutoSize = true;
			this.labelFormat.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelFormat.Location = new System.Drawing.Point(509, 8);
			this.labelFormat.Name = "labelFormat";
			this.labelFormat.Size = new System.Drawing.Size(85, 18);
			this.labelFormat.TabIndex = 6;
			this.labelFormat.Text = "ZZZZZZZZZZZ";
			// 
			// labelLength
			// 
			this.labelLength.AutoSize = true;
			this.labelLength.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelLength.Location = new System.Drawing.Point(331, 8);
			this.labelLength.Name = "labelLength";
			this.labelLength.Size = new System.Drawing.Size(85, 18);
			this.labelLength.TabIndex = 10;
			this.labelLength.Text = "ZZZZZZZZZZZ";
			// 
			// labelFormat__
			// 
			this.labelFormat__.AutoSize = true;
			this.labelFormat__.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelFormat__.Location = new System.Drawing.Point(447, 8);
			this.labelFormat__.Name = "labelFormat__";
			this.labelFormat__.Size = new System.Drawing.Size(56, 18);
			this.labelFormat__.TabIndex = 5;
			this.labelFormat__.Text = "Format:";
			// 
			// labelLength__
			// 
			this.labelLength__.AutoSize = true;
			this.labelLength__.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelLength__.Location = new System.Drawing.Point(271, 8);
			this.labelLength__.Name = "labelLength__";
			this.labelLength__.Size = new System.Drawing.Size(54, 18);
			this.labelLength__.TabIndex = 9;
			this.labelLength__.Text = "Length:";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label2.Location = new System.Drawing.Point(99, 8);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(37, 18);
			this.label2.TabIndex = 3;
			this.label2.Text = "Size:";
			// 
			// panelTexture
			// 
			this.panelTexture.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.panelTexture.AutoScroll = true;
			this.panelTexture.Controls.Add(this.pictureBox);
			this.panelTexture.Location = new System.Drawing.Point(102, 32);
			this.panelTexture.Name = "panelTexture";
			this.panelTexture.Size = new System.Drawing.Size(603, 463);
			this.panelTexture.TabIndex = 11;
			// 
			// UCTexture
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 18F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.Control;
			this.Controls.Add(this.panelTexture);
			this.Controls.Add(this.labelLength);
			this.Controls.Add(this.labelLength__);
			this.Controls.Add(this.labelFormat);
			this.Controls.Add(this.labelFormat__);
			this.Controls.Add(this.labelSize);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.listBoxMipmaps);
			this.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
			this.Name = "UCTexture";
			this.Size = new System.Drawing.Size(710, 500);
			((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
			this.panelTexture.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.PictureBox pictureBox;
		private System.Windows.Forms.ListBox listBoxMipmaps;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label labelSize;
		private System.Windows.Forms.Label labelFormat;
		private System.Windows.Forms.Label labelLength;
		private System.Windows.Forms.Label labelFormat__;
		private System.Windows.Forms.Label labelLength__;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Panel panelTexture;
	}
}
