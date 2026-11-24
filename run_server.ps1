param(
    [string]$Mode
)

switch ($Command) {
    "test"
    {

    }

    "release"
    {

    }
    
    Default {
        Write-Host "잘못된 명령어입니다."
        exit 1
    }
}