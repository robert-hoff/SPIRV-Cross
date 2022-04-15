<h1>SpirvCrossDll.dll</h1>

To build `SpirvCrossDll.dll`

Run `cmake .` in root dir to create Visual Studio project files (tested on **Visual Studio 2019**)

In Visual Studio Solution Explorer add project `/SpirvCrossDll`

Run *Build all*

dll compiles to `/x64/Release/SpirvCrossDll.dll`


<h2> Including dll in C# project</h2>

Create the following method on the C# end

    [DllImport("SpirvCrossDll.dll")]
    private static extern IntPtr CreateSpirvDecompiler();

    [DllImport("SpirvCrossDll.dll")]
    private static extern int PushUInt32(IntPtr decompiler, UInt32 val);

    [DllImport("SpirvCrossDll.dll")]
    private static extern char Parse(IntPtr decompiler);

    [DllImport("SpirvCrossDll.dll")]
    private static extern int GetDataLength(IntPtr decompiler);

    [DllImport("SpirvCrossDll.dll")]
    private static extern char GetChar(IntPtr decompiler, int i);

    private static string DecompileSpirv(byte[] spirv_databytes)
    {
        IntPtr decompiler = CreateSpirvDecompiler();
        for (int i = 0; i < spirv_databytes.Length; i += 4)
        {
            uint b0 = (uint)spirv_databytes[i + 0];
            uint b1 = (uint)spirv_databytes[i + 1];
            uint b2 = (uint)spirv_databytes[i + 2];
            uint b3 = (uint)spirv_databytes[i + 3];
            uint nextUInt32 = b3 + (b2 << 8) + (b1 << 16) + (b0 << 24);
            PushUInt32(decompiler, nextUInt32);
        }
        Parse(decompiler);
        int len = GetDataLength(decompiler);
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < len; i++)
        {
            char c = GetChar(decompiler, i);
            sb.Append(c);
        }
        return sb.ToString();
    }


