param(
  [string]$TestName,
  [switch]$IsSource,
  [string[]]$CFLAG,
  [switch]$Verbose
)

$OWD = Split-Path (Split-Path $MyInvocation.MyCommand.Path)
$SOURCE = "$OWD/source"
$BIN = "$OWD/bin"
$LIBRARY = "$OWD/Library"
$INCLUDE = "$OWD/include"
$TEST = "$OWD/Test"
$TOOLS = "$OWD/Tools"

$Env:CCACHE_DIR = "$BIN/ccache"

function Parse-TestInfo
{
  param(
    [string]$Info
  )
}

function Main
{
   if (-not (Test-Path -Path "$TEST/$TestName.c"))
   {
      return $false
   }

   $TestLang = Split-Path $TestName
   $RTestName = Split-Path $TestName -Leaf

   if (-not (Test-Path -Path "$BIN/Test"))
   {
     mkdir "$BIN/Test"
   }

   if (-not (Test-Path -Path "$BIN/Test/$TestLang"))
   {
     mkdir "$BIN/Test/$TestLang"
   }

   Write-Host "TEST: Test/$TestName.c -> Bin/Test/$TestName.exe"

   if ($Verbose)
   {
     Write-Host "gcc -o $BIN/Test/$TestLang/$RTestName.exe $Test/$TestName.c -L$LIBRARY -I$INCLUDE -l:monsoon.a $CFLAG"
   }

   & "ccache"   "gcc" "-o" "$BIN/Test/$TestLang/$RTestName.exe" "$TEST/$TestName.c" "-L$LIBRARY" "-I$INCLUDE" "-l:monsoon.a" $CFLAG
   if ($?)
   {
      Copy-Item "$BIN/Monsoon.dll" "$BIN/Test/$TestLang"
      return $true
   }
   return $false
}

if ($IsSource)
{
  exit
}

if (-not ($IsSource))
{
  return Main
}
