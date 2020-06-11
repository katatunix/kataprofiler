using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace KataProfiler
{
	public class Secu
	{
		public static bool check()
		{
			var name = System.Net.Dns.GetHostEntry("").HostName;
			return name.Contains("test.com");
		}
	}
}
