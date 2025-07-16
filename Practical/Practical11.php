<?php
header('Content-Type: text/html');

// Sample student records (roll, name, branch)
$students = [
    ['roll' => 1, 'name' => 'Amit Sharma', 'branch' => 'Computer Science'],
    ['roll' => 2, 'name' => 'Priya Singh', 'branch' => 'Electronics & Communication'],
    ['roll' => 3, 'name' => 'Rahul Verma', 'branch' => 'Mechanical Engineering'],
    ['roll' => 4, 'name' => 'Sneha Patel', 'branch' => 'Civil Engineering'],
    ['roll' => 5, 'name' => 'Vikas Gupta', 'branch' => 'Electrical Engineering'],
    ['roll' => 6, 'name' => 'Neha Reddy', 'branch' => 'Computer Science'],
    ['roll' => 7, 'name' => 'Rohan Das', 'branch' => 'Electronics & Communication'],
    ['roll' => 8, 'name' => 'Anjali Nair', 'branch' => 'Mechanical Engineering'],
    ['roll' => 9, 'name' => 'Karan Mehta', 'branch' => 'Civil Engineering'],
    ['roll' => 10, 'name' => 'Pooja Iyer', 'branch' => 'Electrical Engineering'],
];

$q = isset($_GET['q']) ? strtolower(trim($_GET['q'])) : '';

if ($q === '') {
    echo '<em>Type a name or roll number to search for student records.</em>';
    exit;
}

$results = [];
foreach ($students as $student) {
    if (
        strpos(strtolower($student['name']), $q) !== false ||
        strpos((string)$student['roll'], $q) !== false
    ) {
        $results[] = $student;
    }
}

if (count($results) > 0) {
    echo '<ul style="list-style:none;padding:0;">';
    foreach ($results as $student) {
        echo '<li><strong>' . htmlspecialchars($student['name']) . '</strong> | Roll: ' . htmlspecialchars($student['roll']) . ' | ' . htmlspecialchars($student['branch']) . '</li>';
    }
    echo '</ul>';
} else {
    echo '<span style="color:#c00;">No student found.</span>';
} 