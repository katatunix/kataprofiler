using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace KataProfiler
{
	public partial class FormObjectDetail : Form
	{
		public FormObjectDetail()
		{
			InitializeComponent();
		}

		private void FormObjectDetail_FormClosed(object sender, FormClosedEventArgs e)
		{
			Utils.gc();
		}

		private void FormObjectDetail_Load(object sender, EventArgs e)
		{

		}

		protected override bool ProcessCmdKey(ref System.Windows.Forms.Message msg, Keys keyData)
		{
			if (keyData == Keys.Escape)
			{
				this.Close();
				return true;
			}
			return base.ProcessCmdKey(ref msg, keyData);
		}
	}
}
