using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace ConsoleApplication1
{
	class Program
	{
		static StreamWriter writer;
		static StreamWriter writer2;
		static StreamWriter writer3;
		static StreamWriter writer4;
		static StreamWriter writer5;

		static void processLine(String line)
		{
			int i = line.LastIndexOf(';');

			writer.WriteLine( line.Substring(0, i).Trim() + " {" );

			i = line.IndexOf('(');
			int j = line.IndexOf(')');

			String parameters = line.Substring(i + 1, j - i - 1).Trim();
			String[] p = parameters.Split(',');
			String[,] q = new String[p.Length, 2];
			for (int k = 0; k < p.Length; k++)
			{
				p[k] = p[k].Trim();

				int y = p[k].LastIndexOf(' ');
				if (y == -1)
				{
					q[k, 0] = "void";
					q[k, 1] = "";
				}
				else
				{
					q[k, 0] = p[k].Substring(0, y).Trim();
					q[k, 1] = p[k].Substring(y + 1).Trim();
				}
			}

			String tmp = line.Substring(0, i).Trim();
			i = tmp.LastIndexOf(' ');
			String funcName = tmp.Substring(i + 1).Trim();
			String returnType = tmp.Substring(0, i).Trim();


			String shortParams = "";
			for (i = 0; i < p.Length; i++)
			{
				shortParams += q[i, 0];
				if (i < p.Length - 1) shortParams += ", ";
			}

			String myFuncName = "my_" + funcName;
			
			//writer.WriteLine("\tstatic " + returnType + " (*" + myFuncName + ")(" + shortParams + ") = NULL;");
			
            //writer.WriteLine("\tif (!" + myFuncName + ") " + myFuncName + " = " +
            //    "(" + returnType + " (*)(" + shortParams + ")) dlsym(my_handler, \"" + funcName + "\");");

			String vars = "";
			for (i = 0; i < p.Length; i++)
			{
				if (q[i, 1].Length > 0) vars += q[i, 1];
				if (i < p.Length - 1) vars += ", ";
			}

			if (returnType == "void")
			{
				writer.WriteLine("\t" + myFuncName + "(" + vars + ");");
				writer.WriteLine("\tkpServer.on_" + funcName + "(" + vars + ");");
			}
			else
			{
				writer.Write("\t" + returnType + " tmp = ");
				writer.WriteLine(myFuncName + "(" + vars + ");");
				writer.WriteLine("\tkpServer.on_" + funcName + "(" + vars + (vars.Length==0?"":", ") + "tmp);");
				writer.WriteLine("\treturn tmp;");
			}


			writer.WriteLine("}\r\n");

			//
			if (returnType != "void")
			{
				if (p.Length == 1 && q[0, 0] == "void")
					parameters = returnType + " result";
				else
					parameters += ", " + returnType + " result";
			}

			writer2.WriteLine("void KPServer::on_" + funcName + "(" + parameters + ")");
			writer2.WriteLine("{");
			writer2.WriteLine("\tif (getState() == CAPTURING)");
			writer2.WriteLine("\t{");
			writer2.WriteLine("\t}");
			writer2.WriteLine("}\r\n");

			//
			writer3.WriteLine("\tvoid on_" + funcName + "(" + parameters + ");");

			//
			writer4.WriteLine("\tKMT_" + funcName + ",");

			//
			writer5.WriteLine("\tcase KPMessageType.KMT_" + funcName + ":");
			writer5.WriteLine("\t{");
			writer5.WriteLine("\t\tbreak;");
			writer5.WriteLine("\t}");
		}

		static void Main(string[] args)
		{
			StreamReader reader = new StreamReader(@"F:\gl2.h");
			writer = new StreamWriter(@"F:\hook.c");

			writer2 = new StreamWriter(@"F:\server.c");

			writer3 = new StreamWriter(@"F:\server_header.c");
			writer4 = new StreamWriter(@"F:\enum.c");
			writer5 = new StreamWriter(@"F:\switchCase.c");
			writer5.WriteLine("switch (type)");
			writer5.WriteLine("{");
			

			String line;
			while ((line = reader.ReadLine()) != null)
			{
				processLine(line);
			}

			writer5.WriteLine("}");
			writer5.Close();
			writer4.Close();
			writer3.Close();
			writer2.Close();
			writer.Close();
			reader.Close();
		}
	}
}
