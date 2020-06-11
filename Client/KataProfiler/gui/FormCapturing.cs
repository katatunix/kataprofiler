using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using FastColoredTextBoxNS;

namespace KataProfiler
{
	public partial class FormCapturing : Form
	{
		private int m_count;
		CaptureCancelEventHandler m_cancelHandler;

		public FormCapturing(CaptureCancelEventHandler handler)
		{
			InitializeComponent();

			m_cancelHandler = handler;

			m_count = 0;
		}

		private void FormCapturing_Load(object sender, EventArgs e)
		{

		}

		public void onReceiveMsg(Message msg)
		{
			labelMsgCount.Text = (++m_count).ToString();
		}

		private void buttonCancelCapture_Click(object sender, EventArgs e)
		{
			doCancel();
		}

		protected override bool ProcessCmdKey(ref System.Windows.Forms.Message msg, Keys keyData)
		{
			if (keyData == Keys.Escape)
			{
				doCancel();
				return true;
			}
			return base.ProcessCmdKey(ref msg, keyData);
		}

		private void doCancel()
		{
			buttonCancelCapture.Text = "Cancelling...";
			buttonCancelCapture.Enabled = false;
			m_cancelHandler.Invoke();
		}
	}
}
