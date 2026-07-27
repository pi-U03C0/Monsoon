using System.Runtime.InteropServices;

namespace Monsoon;

public class Monsoon
{
  [DllImport("Monsoon.dll",CallingConvention = CallingConvention.Cdecl)]
  public static extern bool MONSInit(ushort[] Components,byte LogLevel);
}

