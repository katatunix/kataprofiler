using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace KataProfiler
{
	static class App
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			if (!Secu.check())
			{
				//MessageBox.Show("You are not allowed to use this tool!", "Oh man", MessageBoxButtons.OK, MessageBoxIcon.Error);
				//return;
			}
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new FormMain());
		}
	}
}
