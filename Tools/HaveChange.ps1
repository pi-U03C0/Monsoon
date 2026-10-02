param(
    [int]$FileIndex,

    [ValidateSet("Read", "Write")]
    [string]$Operation,

    [switch]$IsSource,

    [switch]$Verbose
)

enum Mode
{
    Read
    Write
}

$Operation = [Mode]::$Operation

function Main
{

}

Main
