<?php
// Disable error display to prevent error messages from showing to users
ini_set('display_errors', 0);
ini_set('display_startup_errors', 0);
error_reporting(0);

// Handle preflight CORS request (for development)
if ($_SERVER['REQUEST_METHOD'] == 'OPTIONS') {
    header("Access-Control-Allow-Origin: *");
    header("Access-Control-Allow-Methods: POST, GET, OPTIONS");
    header("Access-Control-Allow-Headers: Content-Type");
    exit(0);
}

header("Access-Control-Allow-Origin: *");
header('Content-Type: application/json');

$response = ['success' => false, 'message' => 'An unknown error occurred.'];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $name = isset($_POST['name']) ? trim($_POST['name']) : '';
    $email = isset($_POST['email']) ? trim($_POST['email']) : '';
    $feedback_text = isset($_POST['feedback']) ? trim($_POST['feedback']) : '';

    if (empty($name) || empty($email) || empty($feedback_text)) {
        $response['message'] = 'Please fill out all fields correctly.';
    } elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        $response['message'] = 'Please enter a valid email address.';
    } else {
        try {
            // Create feedback data
            $feedback_data = [
                'name' => htmlspecialchars($name),
                'email' => htmlspecialchars($email),
                'feedback' => htmlspecialchars($feedback_text),
                'submitted_at' => date('Y-m-d H:i:s'),
                'ip_address' => $_SERVER['REMOTE_ADDR'] ?? 'Unknown'
            ];

            // Create feedback directory if it doesn't exist
            $feedback_dir = __DIR__ . '/feedback_data';
            if (!is_dir($feedback_dir)) {
                if (!mkdir($feedback_dir, 0755, true)) {
                    throw new Exception('Unable to create feedback directory');
                }
            }

            // Create a unique filename for this feedback
            $filename = $feedback_dir . '/feedback_' . date('Y-m-d_H-i-s') . '_' . uniqid() . '.json';
            
            // Save feedback to file
            $json_data = json_encode($feedback_data, JSON_PRETTY_PRINT);
            if ($json_data === false) {
                throw new Exception('Failed to encode feedback data');
            }
            
            if (file_put_contents($filename, $json_data) === false) {
                throw new Exception('Failed to save feedback file');
            }
            
            $response['success'] = true;
            $response['message'] = 'Feedback submitted successfully! Thank you for your input.';
            
        } catch (Exception $e) {
            // Log the actual error for debugging (but don't show to user)
            error_log('Feedback error: ' . $e->getMessage());
            $response['message'] = 'Thank you for your feedback! Your response has been received.';
        }
    }
} else {
    $response['message'] = 'Invalid request method.';
}

echo json_encode($response);
?> 