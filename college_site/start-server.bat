@echo off
title College Site - PHP Server
echo ========================================
echo    College Site - Local Development Server
echo ========================================
echo.
echo Starting PHP server...
echo.
echo Your site will be available at:
echo http://localhost:8000
echo.
echo Press Ctrl+C to stop the server
echo ========================================
echo.

REM Check if PHP is installed
php --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: PHP is not installed or not in PATH
    echo.
    echo Please install PHP or add it to your system PATH
    echo You can download PHP from: https://windows.php.net/download/
    echo.
    pause
    exit /b 1
)

REM Start PHP server
php -S localhost:8000

echo.
echo Server stopped.
pause 