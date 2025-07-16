<?php
header('Content-Type: text/plain');
$thoughts = [
    "Believe you can and you're halfway there.",
    "Every day is a second chance.",
    "Dream big and dare to fail.",
    "Stay positive, work hard, make it happen.",
    "Success is not for the lazy.",
    "Difficult roads often lead to beautiful destinations.",
    "You are stronger than you think.",
    "Great things never come from comfort zones.",
    "Push yourself, because no one else is going to do it for you.",
    "The best time for new beginnings is now."
];
echo $thoughts[array_rand($thoughts)]; 