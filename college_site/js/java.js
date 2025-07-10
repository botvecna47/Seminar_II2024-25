// Theme Toggle Functionality
function toggleTheme() {
    const body = document.body;
    const currentTheme = body.getAttribute('data-theme');
    const newTheme = currentTheme === 'dark' ? 'light' : 'dark';
    body.setAttribute('data-theme', newTheme);
    localStorage.setItem('theme', newTheme);
}

// Week Section Toggle Functionality
function toggleWeekSection(section) {
    const content = section.querySelector('.roadmap-content');
    const icon = section.querySelector('h5 i.fa-chevron-down, h5 i.fa-chevron-up');
    
    if (content.style.display === 'block') {
        content.style.display = 'none';
        icon.classList.remove('fa-chevron-up');
        icon.classList.add('fa-chevron-down');
        section.classList.add('collapsed');
    } else {
        content.style.display = 'block';
        icon.classList.remove('fa-chevron-down');
        icon.classList.add('fa-chevron-up');
        section.classList.remove('collapsed');
    }
}

// Question Toggle Functionality
function toggleQuestion(id) {
    const content = document.getElementById(id);
    const header = content.previousElementSibling;
    const icon = header.querySelector('i');
    
    if (content.style.display === 'block') {
        content.style.display = 'none';
        icon.classList.remove('fa-chevron-up');
        icon.classList.add('fa-chevron-down');
    } else {
        content.style.display = 'block';
        icon.classList.remove('fa-chevron-down');
        icon.classList.add('fa-chevron-up');
    }
}

// Roadmap Section Toggle Functionality
function toggleRoadmapSection(section) {
    const content = section.querySelector('.roadmap-content');
    const icon = section.querySelector('h3 i.fa-chevron-down, h3 i.fa-chevron-up');
    
    if (content.style.display === 'block') {
        content.style.display = 'none';
        icon.classList.remove('fa-chevron-up');
        icon.classList.add('fa-chevron-down');
        section.classList.add('collapsed');
    } else {
        content.style.display = 'block';
        icon.classList.remove('fa-chevron-down');
        icon.classList.add('fa-chevron-up');
        section.classList.remove('collapsed');
    }
}

// Initialize all sections
function initializeSections() {
    // Initialize theme
    const savedTheme = localStorage.getItem('theme') || 'light';
    document.body.setAttribute('data-theme', savedTheme);

    // Initialize week sections
    const weekSections = document.querySelectorAll('.week-section');
    weekSections.forEach(section => {
        const header = section.querySelector('h5');
        const content = section.querySelector('.roadmap-content');
        
        // Add click event to header
        header.addEventListener('click', () => toggleWeekSection(section));
        
        // Add chevron icon if not present
        if (!header.querySelector('i.fa-chevron-down, i.fa-chevron-up')) {
            const icon = document.createElement('i');
            icon.className = 'fas fa-chevron-down';
            header.appendChild(icon);
        }
        
        // Initially hide content
        content.style.display = 'none';
        section.classList.add('collapsed');
    });

    // Initialize practice questions
    const questionHeaders = document.querySelectorAll('.question-header');
    questionHeaders.forEach(header => {
        const content = header.nextElementSibling;
        content.style.display = 'none';
    });
}

// Add event listeners when DOM is loaded
document.addEventListener('DOMContentLoaded', function () {
    // Section tab logic
    document.querySelectorAll('.section-navbar a').forEach(a => {
        a.addEventListener('click', function () {
            document.querySelectorAll('.section-content').forEach(div => div.style.display = 'none');
            document.getElementById('section-' + this.getAttribute('data-section')).style.display = 'block';
            document.querySelectorAll('.section-navbar a').forEach(a2 => a2.classList.toggle('active', a2 === this));
            // Show/hide week navbar if roadmap
            const weekNav = document.querySelector('.week-navbar');
            if (this.getAttribute('data-section') === 'roadmap') {
                if (weekNav) weekNav.style.display = 'flex';
                showWeek('1-2');
            } else {
                if (weekNav) weekNav.style.display = 'none';
            }
        });
    });
    // Week tab logic
    document.querySelectorAll('.week-navbar a').forEach(a => {
        a.addEventListener('click', function () {
            document.querySelectorAll('.week-section').forEach(div => div.style.display = 'none');
            document.querySelector('.week-section[data-week="' + this.getAttribute('data-week') + '"]').style.display = 'block';
            document.querySelectorAll('.week-navbar a').forEach(a2 => a2.classList.toggle('active', a2 === this));
        });
    });
    // Default state
    document.querySelectorAll('.section-content').forEach(div => div.style.display = 'none');
    if (document.getElementById('section-courses')) document.getElementById('section-courses').style.display = 'block';
    // Hide week navbar by default
    const weekNav = document.querySelector('.week-navbar');
    if (weekNav) weekNav.style.display = 'none';
    // Collapse all questions by default
    document.querySelectorAll('.question-content').forEach(content => content.classList.remove('open'));
    // Event delegation for question collapse
    document.querySelectorAll('.practice-questions').forEach(section => {
        section.addEventListener('click', function(e) {
            const header = e.target.closest('.question-header');
            if (header) {
                const content = header.nextElementSibling;
                if (content && content.classList.contains('question-content')) {
                    content.classList.toggle('open');
                }
            }
        });
    });
});

// Bookmark logic for tracker page
(function() {
    const pageKey = 'java-tracker';
    const bookmarkKey = `${pageKey}-bookmarks`;
    function getBookmarks() {
        try {
            return JSON.parse(localStorage.getItem(bookmarkKey)) || [];
        } catch { return []; }
    }
    function setBookmarks(arr) {
        localStorage.setItem(bookmarkKey, JSON.stringify(arr));
    }
    function updateStars() {
        const bookmarks = getBookmarks();
        document.querySelectorAll('.bookmark-star').forEach(star => {
            if (bookmarks.includes(star.dataset.id)) {
                star.classList.add('bookmarked');
                star.innerHTML = '★';
            } else {
                star.classList.remove('bookmarked');
                star.innerHTML = '☆';
            }
        });
    }
    function updateBookmarkedSection() {
        const bookmarks = getBookmarks();
        const section = document.getElementById('bookmarked-section');
        if (!section) return;
        if (bookmarks.length === 0) {
            section.innerHTML = '';
            return;
        }
        let html = '<div style="background:#fff3cd; border:1px solid #ffe082; border-radius:7px; padding:1em 1.2em; margin-bottom:1em; color:#b07219;"><b>Bookmarked Topics:</b><ul style="margin:0.7em 0 0 1.2em;">';
        bookmarks.forEach(id => {
            const label = document.querySelector(`[for='${id}']`);
            if (label) {
                html += `<li style='margin-bottom:0.3em;'><a href="#" data-scroll-id="${id}" style="color:#b07219; text-decoration:underline;">${label.textContent}</a></li>`;
            }
        });
        html += '</ul></div>';
        section.innerHTML = html;
        // Scroll to item on click
        section.querySelectorAll('a[data-scroll-id]').forEach(a => {
            a.onclick = function(e) {
                e.preventDefault();
                const el = document.getElementById(this.dataset.scrollId);
                if (el) {
                    el.scrollIntoView({behavior:'smooth', block:'center'});
                    el.focus && el.focus();
                }
            };
        });
    }
    document.addEventListener('DOMContentLoaded', function() {
        updateStars();
        updateBookmarkedSection();
        document.querySelectorAll('.bookmark-star').forEach(star => {
            star.onclick = function(e) {
                e.preventDefault();
                const id = this.dataset.id;
                let bookmarks = getBookmarks();
                if (bookmarks.includes(id)) {
                    bookmarks = bookmarks.filter(x => x !== id);
                } else {
                    bookmarks.push(id);
                }
                setBookmarks(bookmarks);
                updateStars();
                updateBookmarkedSection();
            };
        });
    });
})(); 