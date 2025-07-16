<?php
// Database connection settings
$host = 'localhost';
$user = 'root';
$pass = '';
$dbname = 'student'; // Change to your DB name

$conn = new mysqli($host, $user, $pass, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Get sort order from query string, default to ASC
$order = (isset($_GET['order']) && strtolower($_GET['order']) === 'desc') ? 'DESC' : 'ASC';

// Fetch sorted records
$sql = "SELECT roll, name, branch FROM students ORDER BY name $order";
$result = $conn->query($sql);

// Output only the table
echo '<table style="width:100%; border-collapse: collapse;">';
echo '<tr><th style="background:#0078d7;color:#fff;padding:8px 12px;">Roll</th><th style="background:#0078d7;color:#fff;padding:8px 12px;">Name</th><th style="background:#0078d7;color:#fff;padding:8px 12px;">Branch</th></tr>';
if ($result && $result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        echo "<tr>
                <td style='padding:8px 12px;border-bottom:1px solid #ddd;'>" . htmlspecialchars($row['roll']) . "</td>
                <td style='padding:8px 12px;border-bottom:1px solid #ddd;'>" . htmlspecialchars($row['name']) . "</td>
                <td style='padding:8px 12px;border-bottom:1px solid #ddd;'>" . htmlspecialchars($row['branch']) . "</td>
              </tr>";
    }
} else {
    echo "<tr><td colspan='3' style='padding:8px 12px;'>No records found.</td></tr>";
}
echo '</table>';
$conn->close(); 