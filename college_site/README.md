# College Study Portal

A comprehensive learning platform with interactive tutorials, practice trackers, and quizzes for programming languages and computer science subjects.

## Features

- **Interactive Learning**: Python and Java tutorials with 12-week roadmaps
- **Practice Trackers**: Progress tracking with localStorage persistence
- **Quizzes**: Comprehensive quizzes for each programming language
- **OS Practicals**: Interactive operating system algorithm simulations
- **Feedback System**: User feedback collection with local storage
- **Rating System**: Star-based ratings for each language page with average display

## Quick Start

### Option 1: Using the Batch File (Recommended)
1. **Double-click** `start-server.bat`
2. **Open your browser** and go to `http://localhost:8000`
3. **Press Ctrl+C** in the command window to stop the server

### Option 2: Manual Start
1. **Open Command Prompt** in this folder
2. **Run**: `php -S localhost:8000`
3. **Open browser** and go to `http://localhost:8000`

## Requirements

- **PHP** (version 7.0 or higher)
- **Web Browser** (Chrome, Firefox, Safari, Edge)

## File Structure

```
college_site/
├── index.html              # Main homepage
├── start-server.bat        # Quick start script
├── feedback.php            # Feedback processing
├── rating.php              # Rating system processing
├── css/                    # Stylesheets
├── js/                     # JavaScript files
├── languages/              # Programming language pages
│   ├── python.html         # Python main page
│   ├── python-tracker.html # Python progress tracker
│   ├── python-quiz.html    # Python quiz
│   ├── java.html           # Java main page
│   ├── java-tracker.html   # Java progress tracker
│   └── java-quiz.html      # Java quiz
├── programs/               # C program examples
├── feedback_data/          # Feedback storage (created automatically)
└── ratings_data/           # Rating storage (created automatically)
```

## Features Overview

### Programming Languages
- **Python**: 12-week learning roadmap with practice problems
- **Java**: Comprehensive Java tutorial with OOP concepts

### Interactive Elements
- **Progress Tracking**: Check off completed topics and problems
- **Quizzes**: Test your knowledge with multiple-choice questions
- **OS Simulations**: Visualize operating system algorithms
- **Rating System**: Rate each language page (1-5 stars) and see average ratings

### User Experience
- **Dark/Light Theme**: Toggle between themes
- **Responsive Design**: Works on desktop and mobile
- **Local Storage**: Progress saved in your browser
- **Real-time Ratings**: See average ratings and total number of votes

## Rating System

The rating system allows users to:
- **Rate pages**: Click on stars (1-5) to rate Java and Python pages
- **View averages**: See the average rating and total number of ratings
- **One-time rating**: Each user can only rate once per page
- **Persistent storage**: Ratings are stored in JSON files locally

### Rating Data Storage
- **Location**: `ratings_data/` directory
- **Files**: `java_ratings.json` and `python_ratings.json`
- **Format**: JSON with rating value, timestamp, and IP address
- **Privacy**: No personal information collected, only IP for duplicate prevention

## Troubleshooting

### PHP Not Found
If you get "PHP is not installed" error:
1. Download PHP from https://windows.php.net/download/
2. Add PHP to your system PATH
3. Restart Command Prompt and try again

### Port Already in Use
If port 8000 is busy:
1. Stop the server (Ctrl+C)
2. Edit `start-server.bat` and change `8000` to `8001` or another port
3. Run the batch file again

### Rating System Issues
If ratings don't work:
1. Make sure you're running the PHP server (not just opening HTML files)
2. Check that `rating.php` is in the same directory as the language pages
3. Ensure the `ratings_data` directory has write permissions

## Development

To modify the site:
- Edit HTML files for content changes
- Modify CSS files for styling
- Update JavaScript files for functionality
- Add new language pages in the `languages/` folder
- Extend rating system to other pages by adding similar star elements

## Support

For issues or questions, check the feedback system or contact the development team. 