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

// Get the page identifier (java or python)
$page = isset($_GET['page']) ? $_GET['page'] : '';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Handle rating submission
    $rating = isset($_POST['rating']) ? intval($_POST['rating']) : 0;
    $page = isset($_POST['page']) ? $_POST['page'] : '';
    
    if ($rating < 1 || $rating > 5) {
        $response['message'] = 'Invalid rating value. Please provide a rating between 1 and 5.';
    } elseif (empty($page) || !in_array($page, ['java', 'python'])) {
        $response['message'] = 'Invalid page identifier.';
    } else {
        try {
            // Create ratings directory if it doesn't exist
            $ratings_dir = __DIR__ . '/ratings_data';
            if (!is_dir($ratings_dir)) {
                if (!mkdir($ratings_dir, 0755, true)) {
                    throw new Exception('Unable to create ratings directory');
                }
            }

            // Load existing ratings
            $ratings_file = $ratings_dir . '/' . $page . '_ratings.json';
            $ratings_data = [];
            
            if (file_exists($ratings_file)) {
                $existing_data = file_get_contents($ratings_file);
                if ($existing_data !== false) {
                    $ratings_data = json_decode($existing_data, true) ?: [];
                }
            }

            // Add new rating
            $new_rating = [
                'rating' => $rating,
                'timestamp' => date('Y-m-d H:i:s'),
                'ip_address' => $_SERVER['REMOTE_ADDR'] ?? 'Unknown'
            ];
            
            $ratings_data[] = $new_rating;
            
            // Save updated ratings
            $json_data = json_encode($ratings_data, JSON_PRETTY_PRINT);
            if ($json_data === false) {
                throw new Exception('Failed to encode ratings data');
            }
            
            if (file_put_contents($ratings_file, $json_data) === false) {
                throw new Exception('Failed to save ratings file');
            }
            
            // Calculate new average
            $total_ratings = count($ratings_data);
            $sum_ratings = array_sum(array_column($ratings_data, 'rating'));
            $average_rating = $total_ratings > 0 ? round($sum_ratings / $total_ratings, 1) : 0;
            
            $response['success'] = true;
            $response['message'] = 'Thank you for your rating!';
            $response['data'] = [
                'average_rating' => $average_rating,
                'total_ratings' => $total_ratings,
                'your_rating' => $rating
            ];
            
        } catch (Exception $e) {
            // Log the actual error for debugging (but don't show to user)
            error_log('Rating error: ' . $e->getMessage());
            $response['message'] = 'Thank you for your rating! Your response has been received.';
        }
    }
} elseif ($_SERVER["REQUEST_METHOD"] == "GET") {
    // Handle rating retrieval
    if (empty($page) || !in_array($page, ['java', 'python'])) {
        $response['message'] = 'Invalid page identifier.';
    } else {
        try {
            $ratings_file = __DIR__ . '/ratings_data/' . $page . '_ratings.json';
            
            if (file_exists($ratings_file)) {
                $ratings_data = json_decode(file_get_contents($ratings_file), true) ?: [];
                
                $total_ratings = count($ratings_data);
                $sum_ratings = array_sum(array_column($ratings_data, 'rating'));
                $average_rating = $total_ratings > 0 ? round($sum_ratings / $total_ratings, 1) : 0;
                
                $response['success'] = true;
                $response['data'] = [
                    'average_rating' => $average_rating,
                    'total_ratings' => $total_ratings
                ];
            } else {
                $response['success'] = true;
                $response['data'] = [
                    'average_rating' => 0,
                    'total_ratings' => 0
                ];
            }
            
        } catch (Exception $e) {
            error_log('Rating retrieval error: ' . $e->getMessage());
            $response['message'] = 'Unable to load ratings.';
        }
    }
} else {
    $response['message'] = 'Invalid request method.';
}

echo json_encode($response);
?> 