param
(
   [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
   [switch]$ClearFile,

   [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
   [string[]]$D,

   [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
   [string[]]$Args,

   [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
   [switch]$RunExe,

   [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
   [switch]$IsSource,

   [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
   [string]$TestName = "-=-",

   [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
   [switch]$MakeMonsoonDLL,

   [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
   [switch]$CompileMonsoon,

   [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
   [int]$CoreConuter = 3
)

$OWD = Split-Path $MyInvocation.MyCommand.Path
$SOURCE = "$OWD/source"
$BIN = "$OWD/bin"
$LIBRARY = "$OWD/Library"
$INCLUDE = "$OWD/include"
$CFLAG = @("-Wall","-Wextra","-Wno-discarded-qualifiers","-Wno-unused-parameter")
$TEST = "$OWD/Test"
$TOOLS = "$OWD/Tools"

$Verbose = $false

$Env:CCACHE_DIR = "$BIN/ccache"

function ClearFile
{
  remove-item -r $BIN/*
}

function Get-LogDefine
{
  param(
    [string]$Name,
    [string]$L_TOOLS="-=-",
    [string]$L_LIB="-=-"
  )

  $__Tools = $L_TOOLS
  $lib = $L_LIB

  if ($__Tools -eq "-=-")
  {
    $__Tools = $TOOLS
  }

  if ($lib -eq "-=-")
  {
    $lib = $LIBRARY
  }

  try { $file_number = (& "$__Tools\FileIndex.ps1" -IndexFile "$lib/FileIndex.index" -Name $Name)[0] }
  catch { (& "$__Tools\FileIndex.ps1" -Create -IndexFile "$lib/FileIndex.index" -SourcePath $SOURCE) }

  try { $project_part = (& "$__Tools\FileIndex.ps1" -IndexFile "$lib/FileIndex.index" -Name (Split-Path $Name))[0] }
  catch { (& "$__Tools\FileIndex.ps1" -Create -IndexFile "$lib/FileIndex.index" -SourcePath $SOURCE) }

  $define = ("-D__FILE_NUMBER__=$file_number","-D__PROJECT_PART__=$project_part")

  return $define
}

function Compile-Monsoon
{
  Write-Host "Compileing Monsoon"

  if (-not (Test-Path -Path "$BIN/Monsoon"))
  {
    mkdir "$BIN/Monsoon" | Out-Null
  }

  $DidError = $false
  $SOURCE_OBJ = (Get-ChildItem "$SOURCE" -r -Name -File *.c) | ForEach-Object {
    echo "$_".Replace("\","/")
  }

  $SOURCE_PATH = (Get-ChildItem "$SOURCE" -r -Name -Directory) | ForEach-Object {
    if (-not (Test-Path -Path "$BIN/Monsoon/$_"))
    {
      New-Item -ItemType Directory -Path "$BIN/Monsoon/$_"
    }
  }

  echo $SOURCE_OBJ

  $GetLogDefine = ${function:Get-LogDefine}.ToString()

  $Results = $SOURCE_OBJ | ForEach-Object -Parallel {
    $function:Get_LogDefine = [scriptblock]::Create($using:GetLogDefine)

    Write-Host "SRC: Source/$_ -> Bin/Monsoon/$_.o"

    if ($using:Verbose)
    {
      Write-Host "gcc -o $using:BIN/Monsoon/$_.o -c  $using:SOURCE/$_ -I$using:INCLUDE $using:CFLAG $(Get_LogDefine -Name "$using:SOURCE/$_" -L_TOOLS $using:TOOLS -L_LIB $using:LIBRARY)"
    }

    & "ccache" "gcc" "-o" "$using:BIN/Monsoon/$_.o" "-c" "$using:SOURCE/$_" "-I$using:INCLUDE" $using:CFLAG $(Get_LogDefine -Name "$using:SOURCE/$_" -L_TOOLS $using:TOOLS -L_LIB $using:LIBRARY)
    return ($LASTEXITCODE -ne 0)

  } -ThrottleLimit $CoreConuter

  $DidError = $Results -contains $true
  return (-not ($DidError))
}

function Make-MonsoonDLL
{
  if (-not (Test-Path -Path "$BIN/Monsoon/LibInit.c.o"))
  {
    if (-not (Compile-Monsoon))
    {
      return $false
    }
  }

  $OBJECT = (Get-ChildItem -Path "$BIN/Monsoon" -r -Name -File) | Foreach-Object {
    echo "$BIN/Monsoon/$_"
  }

  if ($Verbose)
  {
    Write-Host "gcc -o $BIN/Monsoon.dll $OBJECT -shared -Wl,--out-implib,$LIBRARY/Monsoon.a"
  }

  Write-Host "DLL: -> Bin/Monsoon.dll"
  & "ccache" "gcc" "-o" "$BIN/Monsoon.dll" $OBJECT "-shared" "-Wl,--out-implib,$LIBRARY/Monsoon.a" "-lShlwapi"

  return $true
}

function Compile-Test
{
  param(
    [string]$Name
  )

  if (Test-Path -Path "$TEST/$Name.c")
  {
    Write-Host "TEST: Test/$Name.c -> Bin/$Name.exe"
    if ($Verbose)
    {
      Write-Host "gcc -o $BIN/$Name.exe $TEST/$Name.c -L$LIBRARY -I$INCLUDE -l:monsoon.a $CFLAG"
    }
    & "ccache" "gcc" "-o" "$BIN/$Name.exe" "$TEST/$Name.c" "-L$LIBRARY" "-I$INCLUDE" "-l:monsoon.a" $CFLAG
    return $?
  }
  else
  {
    Write-Host "File $TEST/$Name.c was not Found"
    return $false
  }

  return $true
}

if ($PSCmdlet.MyInvocation.BoundParameters["Verbose"].IsPresent)
{
  $Verbose = $true
  echo "Verbose"
}

if ($D.Length -ne 0)
{
  $D | ForEach-Object {
    $CFLAG += "-D$_"
  }
}

if ($Args.Length -ne 0)
{
  $Args | ForEach-Object {
    $CFLAG += "$_"
  }
}

if ($IsSource)
{
  exit
}

if (-not (Test-Path -Path "$BIN"))
{
  mkdir $BIN | Out-Null
}

if ($PSBoundParameters.ContainsKey("ClearFile"))
{
  ClearFile
  exit
}

if (-not (Test-Path -Path "$LIBRARY/FileIndex.index"))
{
  & "$TOOLS/FileIndex.ps1" -CreateIndex -IndexFile "$LIBRARY/FileIndex.index" -SourcePath $SOURCE
}


if ((-not (Test-Path -Path "$BIN/Monsoon/LibInit.c.o")) -or ($CompileMonsoon))
{
  if (-not (Compile-Monsoon))
  {
    Write-Host "Error Compileing Monsoon"
    exit 1
  }
}

if ((-not (Test-Path -Path "$BIN/Monsoon.dll")) -or ($MakeMonsoonDLL))
{
  if (-not (Make-MonsoonDLL))
  {
    Write-Host "Error Compileing Monsoon DLL"
    exit 1
  }
}

if ($TestName -ne "-=-")
{
  if (-not (Compile-Test $TestName))
  {
    Write-Host "Error Compileing Test `"$TestName`""
    exit 1
  }

  if ($RunExe)
  {
    & "$BIN/$TestName.exe"

    $Message = "`e[32mSUCCESS`e[0m"
    if ($LASTEXITCODE -eq -1073741819)
    {
      $Message = "`e[31mSEGSEVG`e[0m"
    }
    if ($LASTEXITCODE -eq -1073741795)
    {
      $Message = "`e[31mILLEGAL INSTRUCTION`e[0m"
    }
    if ($LASTEXITCODE -eq -1073740940)
    {
      $Message = "`e[31mHEAP CORRUPTION`e[0m"
    }
    if ($LASTEXITCODE -eq -1073741676)
    {
      $Message = "`e[31mDIVIDE BY ZERO`e[0m"
    }
    if ($LASTEXITCODE -eq -1073740791)
    {
      $Message = "`e[31mBUFFER OVERRUN`e[0m"
    }
    Write-Host "`nLASTEXITCODE: $LASTEXITCODE $Message" -nonewline
  }
}
