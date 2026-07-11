param(
  [string]$SourcePath,
  [string]$IndexFile="-=-",
  [int]$Index=-1,
  [string]$Name = "-=-"
)

$OWD = Split-Path $MyInvocation.MyCommand.Path
$script:CurrentIndex = 0

function Add-Index
{
  param(
    [string]$Name
  )

  $Type = "F"

  if (Test-Path -Path $Name -PathType Container)
  {
    $Type = "D"
  }

  $index = "$script:CurrentIndex,$Type,$Name`n"
  $script:CurrentIndex += 1

  return $index
}

function Create-Index
{
  param(
    [string]$Source
  )

  $Index = ""

  foreach ($File in (Get-ChildItem $Source -r -name))
  {
    $Index = "$Index$(Add-Index "$Source/$File")"
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

  Get-Content $IndexFile
}

function Main
{
  param(
    [string]$SourcePath,
    [string]$IndexFile
  )

  $CreateFile = $true
  $IndexFileIndex = $false

  if ($IndexFile -eq "-=-")
  {
    $IndexFilePath = "$(pwd)/FileIndex.index"
  }
  else
  {
    $IndexFilePath = $IndexFile
  }

  if (($Index -ne -1) -or ($Name -ne "-=-"))
  {
    $IndexFileIndex = $true
  }

  if ($CreateFile)
  {
    (Create-Index -Source $SourcePath) > $IndexFilePath
  }
  elseif ($IndexFileIndex)
  {
    echo "dskdjskjd"
    if (-not(Test-path $IndexFilePath))
    {
      Write-Host "Index File Does not Exists at `"$IndexFilePath`""
      exit 1
    }
    return Get-Index $IndexFilePath -Index $Index -Name $Name
  }
}

$S = $SourcePath
if ($SourcePath -eq "")
{
  $S = (pwd).path
}

return Main $S $IndexFile
