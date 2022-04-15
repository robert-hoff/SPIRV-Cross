<h1>SpirvCrossDll.dll</h1>

To build `SpirvCrossDll.dll`

Run `cmake .` in root dir to create Visual Studio project files (tested on **Visual Studio 2019**) - requires `MSVC v143 C++ x64/x86 build tools` (comes with Windows SDK)

Open  `./SPIRV-Cross.sln`

Run *Build solution* `Release` version

Then add *existing* project `/SpirvCrossDll/SpirvCrossDll.vcxproj`

Build SpirvCrossDll project, dll compiles to `/x64/Release/SpirvCrossDll.dll`.

Alternatively **download the dll** here https://github.com/robert-hoff/SPIRV-Cross/blob/spirvdll/SpirvCrossDll.dll


<h2>Including in C# project</h2>

Copy `SpirvCrossDll.dll` into C# project and add it as a reference.

Create the following method.

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

Call `DecompileSpirv(byte[] spirv_databytes)` spirv bytecode will be decompiled into a GLSL string.


<h2>Example use</h2>

<h3>With VRF</h3>

    string HLALYX_VULKAN_SHADERS_VPK = "[hlvr-dir]/game/hlvr/shaders_vulkan_dir.vpk";
    string TARGET_VCS_FILE = "/shaders/vfx/solidcolor_vulkan_50_vs.vcs";
    var package = new SteamDatabase.ValvePak.Package();
    package.Read(HLALYX_VULKAN_SHADERS_VPK);
    package.ReadEntry(package.FindEntry(TARGET_VCS_FILE), out byte[] vcsBytes);
    ShaderFile shaderFile = new ShaderFile();
    shaderFile.Read(TARGET_VCS_FILE, new MemoryStream(vcsBytes));
    VulkanSource vulkanSource = (VulkanSource) shaderFile.GetZFrameFile(0).gpuSources[0];
    byte[] spirvBytes = vulkanSource.GetSpirvBytes();
    string decompiledSpirv = DecompileSpirv(spirvBytes);


<h3>With Asset Ripper</h3>

Intercept Spirv data in `ShaderVulkanExporter.ExportSnippet(TextWriter writer, Stream stream, int offset, int size)`
In the statement

    if (SmolvDecoder.Decode(stream, size, decodedStream))
    {
      // decodedStream is the spirv encoding
    }

Run

    byte[] spirvBytes = decodedStream.ToArray();
    string decompiledSpirv = DecompileSpirv(spirvBytes);



<h2>Sample output</h2>

Game Ballistic Overkill (Unity),  Ballistic/UI/BloodSplatter vulkan-shader[0]

    #version 450

    layout(binding = 0, std140) uniform _18_20
    {
        vec4 _m0[4];
        vec4 _m1[4];
        vec4 _m2;
    } _20;

    layout(location = 0) in vec4 _11;
    layout(location = 0) out vec2 vs_TEXCOORD0;
    layout(location = 2) in vec2 _86;
    layout(location = 1) out vec4 _96;
    layout(location = 1) in vec4 _97;
    vec4 _9;
    vec4 _48;

    void main()
    {
        _9 = _11.yyyy * _20._m0[1];
        _9 = (_20._m0[0] * _11.xxxx) + _9;
        _9 = (_20._m0[2] * _11.zzzz) + _9;
        _9 += _20._m0[3];
        _48 = _9.yyyy * _20._m1[1];
        _48 = (_20._m1[0] * _9.xxxx) + _48;
        _48 = (_20._m1[2] * _9.zzzz) + _48;
        gl_Position = (_20._m1[3] * _9.wwww) + _48;
        vs_TEXCOORD0 = (_86 * _20._m2.xy) + _20._m2.zw;
        _96 = _97;
        gl_Position.y = -gl_Position.y;
    }




