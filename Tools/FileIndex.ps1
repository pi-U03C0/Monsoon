param
(
  [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
  [switch]$CreateIndex,

  [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
  [switch]$IsSource,

  [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
  [int]$NameIndex=-1,

  [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
  [string]$SourcePath="-=-",

  [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
  [string]$IndexFile="-=-",

  [Parameter(Mandatory=$false, ValueFromPipeline=$true)]
  [string]$Name = "-=-"
)

$OWD = Split-Path $MyInvocation.MyCommand.Path
$script:CurrentFileIndex = 0
$script:CurrentDirectoryIndex = 0

function Add-Index
{
  param(
    [string]$Name
  )

  if (Test-Path -Path $Name -PathType Container)
  {
    $Type = "D"
    $index = "$script:CurrentFileIndex,$Type,$Name`n"
    $script:CurrentFileIndex += 1
  }
  else
  {
    $Type = "F"
    $index = "$script:CurrentDirectoryIndex,$Type,$Name`n"
    $script:CurrentDirectoryIndex += 1
  }

  return $index
}

function Create-Index
{
  param(
    [string]$Source
  )

  $Index = Add-Index ((Get-Item $Source).FullName).TrimEnd([System.IO.Path]::DirectorySeparatorChar)

  foreach ($File in (Get-ChildItem $Source -r -fo))
  {
    $Index = "$Index$(Add-Index "$File")"
  }

  return  $Index
}

function Get-Index
{
  param(
    [string]$IndexFile,
    [int]$Index=-1,
    [string]$Name
  )

  $Indexs = Get-Content $IndexFile
  foreach ($indexs in $Indexs.Split("`n"))
  {
    $Index_Split = $indexs.Split(",")

    if ($Index_Split[0] -eq "") {continue}
    if ($Index_Split.Length -ne 3)
    {
      return -1
    }

    if ($Index_Split[0] -eq "$Index")
    {
      return ($Index_Split[1],$Index_Split[2])
    }
    if ((Resolve-Path $Index_Split[2]).Path -eq (Resolve-Path "$Name").Path)
    {
      return ($Index_Split[0],$Index_Split[1])
    }
  }
  return -2
}

function Main
{
  param(
    [string]$SourcePath
  )

  $IndexFilePath = $IndexFile
  if ($IndexFile -eq "-=-")
  {
    $IndexFilePath = "$(pwd)/FileIndex.index"
  }

  if ($CreateIndex)
  {
    (Create-Index -Source $SourcePath) > $IndexFilePath
    Write-host "index file at `"$IndexFilePath`""
  }
  else
  {
    if (-not (Test-Path -Path $IndexFilePath))
    {
      Write-host "FileIndex does not exists at `"$IndexFilePath`""
      exit 1
    }
    return Get-Index -IndexFile $IndexFilePath -Index $NameIndex -Name $Name
  }
}

$S = $SourcePath
if ($SourcePath -eq "-=-")
{
  $S = (pwd).path
}

if ($IsSource)
{
   return
}

return Main $S
