<?php
// File to store the visitor count
$counterFile = 'counter.txt';

// Check if the file exists, if not create it and initialize with 0
if (!file_exists($counterFile)) {
    file_put_contents($counterFile, '0');
}

// Read the current count
$count = (int)file_get_contents($counterFile);

// Increment the count
$count++;

// Write the new count back to the file
file_put_contents($counterFile, $count);

// Display the count
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Visitor Counter</title>
    <style>
        body {
            background: #f7f7f7;
            font-family: Arial, sans-serif;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            margin: 0;
        }
        .counter-container {
            background: #fff;
            padding: 2rem 3rem;
            border-radius: 12px;
            box-shadow: 0 2px 12px rgba(0,0,0,0.08);
            text-align: center;
        }
        h1 {
            color: #333;
            margin-bottom: 1rem;
        }
        p {
            font-size: 1.2rem;
            color: #555;
        }
        strong {
            color: #0078d7;
            font-size: 1.5rem;
        }
    </style>
</head>
<body>
    <div class="counter-container">
        <h1>Welcome to the Visitor Counter Page!</h1>
        <p>You are visitor number: <strong><?php echo $count; ?></strong></p>
    </div>
</body>
</html>
