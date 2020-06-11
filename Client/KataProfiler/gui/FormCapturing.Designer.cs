namespace KataProfiler
{
	partial class FormCapturing
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
			this.progressBar1 = new System.Windows.Forms.ProgressBar();
			this.label1 = new System.Windows.Forms.Label();
			this.labelMsgCount = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.buttonCancelCapture = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// progressBar1
			// 
			this.progressBar1.Location = new System.Drawing.Point(14, 36);
			this.progressBar1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.progressBar1.MarqueeAnimationSpeed = 10;
			this.progressBar1.Name = "progressBar1";
			this.progressBar1.Size = new System.Drawing.Size(356, 20);
			this.progressBar1.Style = System.Windows.Forms.ProgressBarStyle.Marquee;
			this.progressBar1.TabIndex = 3;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(85, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(65, 18);
			this.label1.TabIndex = 0;
			this.label1.Text = "Received";
			// 
			// labelMsgCount
			// 
			this.labelMsgCount.AutoSize = true;
			this.labelMsgCount.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelMsgCount.ForeColor = System.Drawing.Color.Blue;
			this.labelMsgCount.Location = new System.Drawing.Point(168, 9);
			this.labelMsgCount.Name = "labelMsgCount";
			this.labelMsgCount.Size = new System.Drawing.Size(15, 18);
			this.labelMsgCount.TabIndex = 1;
			this.labelMsgCount.Text = "0";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label3.Location = new System.Drawing.Point(221, 9);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(78, 18);
			this.label3.TabIndex = 2;
			this.label3.Text = "message(s)";
			// 
			// buttonCancelCapture
			// 
			this.buttonCancelCapture.Location = new System.Drawing.Point(142, 66);
			this.buttonCancelCapture.Name = "buttonCancelCapture";
			this.buttonCancelCapture.Size = new System.Drawing.Size(101, 30);
			this.buttonCancelCapture.TabIndex = 4;
			this.buttonCancelCapture.Text = "Cancel";
			this.buttonCancelCapture.UseVisualStyleBackColor = true;
			this.buttonCancelCapture.Click += new System.EventHandler(this.buttonCancelCapture_Click);
			// 
			// FormCapturing
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 18F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(384, 108);
			this.ControlBox = false;
			this.Controls.Add(this.buttonCancelCapture);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.labelMsgCount);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.progressBar1);
			this.Font = new System.Drawing.Font("Calibri", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "FormCapturing";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Capturing...";
			this.Load += new System.EventHandler(this.FormCapturing_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ProgressBar progressBar1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label labelMsgCount;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Button buttonCancelCapture;

	}
}