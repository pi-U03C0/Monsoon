param
(
  [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
  [switch]$IsSource,

  [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
  [switch]$IncludeTest,

  [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
  [string]$Config,

  [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
  [switch]$Run
)

$OWD = Split-Path $MyInvocation.MyCommand.Path

function Main
{

  return $true
}

if ($IsSource)
{
   return
}

if ($Run)
{
  return Main
}
