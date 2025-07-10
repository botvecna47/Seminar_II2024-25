document.addEventListener('DOMContentLoaded', () => {
    // Copy code functionality
    document.querySelectorAll('.copy-button').forEach(button => {
        button.addEventListener('click', () => {
            const codeBlock = button.nextElementSibling;
            const code = codeBlock.textContent;
            navigator.clipboard.writeText(code).then(() => {
                const successMessage = document.querySelector('.success-message') || createSuccessMessage();
                successMessage.style.display = 'block';
                setTimeout(() => successMessage.style.display = 'none', 2000);
            });
        });
    });
    function createSuccessMessage() {
        const message = document.createElement('div');
        message.className = 'success-message';
        message.textContent = 'Code copied!';
        message.style.cssText = 'position: fixed; top: 20px; right: 20px; padding: 10px; background: #4CAF50; color: white; display: none;';
        document.body.appendChild(message);
        return message;
    }
    // Smooth scrolling for navigation
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', (e) => {
            e.preventDefault();
            const target = document.querySelector(anchor.getAttribute('href'));
            if (target) {
                target.scrollIntoView({ behavior: 'smooth' });
            }
        });
    });
    // Resource link hover effect
    document.querySelectorAll('.resource-list a').forEach(link => {
        link.addEventListener('mouseenter', () => link.style.transform = 'translateX(10px)');
        link.addEventListener('mouseleave', () => link.style.transform = 'translateX(0)');
    });
    // Syntax highlighting on hover
    document.querySelectorAll('pre').forEach(block => {
        block.addEventListener('mouseenter', () => block.style.backgroundColor = '#f0f0f0');
        block.addEventListener('mouseleave', () => block.style.backgroundColor = '');
    });
    // Progress tracking for resources
    let completedTopics = JSON.parse(localStorage.getItem('completedTopics')) || [];
    document.querySelectorAll('.resource-list a').forEach(link => {
        const topicId = link.getAttribute('href').split('#')[1];
        if (completedTopics.includes(topicId)) {
            link.classList.add('completed');
            addCheckmark(link);
        }
        link.addEventListener('click', () => {
            if (!completedTopics.includes(topicId)) {
                completedTopics.push(topicId);
                localStorage.setItem('completedTopics', JSON.stringify(completedTopics));
                link.classList.add('completed');
                addCheckmark(link);
            }
        });
    });
    function addCheckmark(link) {
        const checkmark = document.createElement('i');
        checkmark.className = 'fas fa-check';
        checkmark.style.marginLeft = '10px';
        link.appendChild(checkmark);
    }
    // Scroll to top button
    const scrollButton = document.createElement('button');
    scrollButton.innerHTML = '↑';
    scrollButton.className = 'scroll-top';
    scrollButton.style.cssText = 'position: fixed; bottom: 20px; right: 20px; display: none;';
    document.body.appendChild(scrollButton);
    window.addEventListener('scroll', () => {
        scrollButton.style.display = window.scrollY > 300 ? 'block' : 'none';
    });
    scrollButton.addEventListener('click', () => {
        window.scrollTo({ top: 0, behavior: 'smooth' });
    });
    // Theme toggle
    function setTheme(theme) {
        document.body.setAttribute('data-theme', theme);
        localStorage.setItem('theme', theme);
        const themeIcon = document.querySelector('.theme-toggle i');
        if (themeIcon) {
            if (theme === 'dark') {
                themeIcon.classList.remove('fa-moon');
                themeIcon.classList.add('fa-sun');
                themeIcon.setAttribute('title', 'Switch to light mode');
            } else {
                themeIcon.classList.remove('fa-sun');
                themeIcon.classList.add('fa-moon');
                themeIcon.setAttribute('title', 'Switch to dark mode');
            }
        }
    }
    function toggleTheme() {
        const current = document.body.getAttribute('data-theme') || 'light';
        const next = current === 'dark' ? 'light' : 'dark';
        setTheme(next);
    }
    const savedTheme = localStorage.getItem('theme') || 'light';
    setTheme(savedTheme);
    const themeToggleBtn = document.querySelector('.theme-toggle');
    if (themeToggleBtn) {
        themeToggleBtn.addEventListener('click', toggleTheme);
    }
    // Question collapse/uncollapse
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
    // Section and week tab navigation
    function showSection(section) {
        document.querySelectorAll('.section-content').forEach(div => {
            div.style.display = 'none';
        });
        document.getElementById('section-' + section).style.display = 'block';
        document.querySelectorAll('.section-navbar a').forEach(a => {
            a.classList.toggle('active', a.getAttribute('data-section') === section);
        });
        if (section === 'roadmap') {
            document.querySelector('.week-navbar').style.display = 'flex';
            showWeekTab('1-2');
        } else {
            const weekNav = document.querySelector('.week-navbar');
            if (weekNav) weekNav.style.display = 'none';
        }
    }
    document.querySelectorAll('.section-navbar a').forEach(a => {
        a.addEventListener('click', function () {
            showSection(this.getAttribute('data-section'));
        });
    });
    document.querySelectorAll('.week-navbar a').forEach(a => {
        a.addEventListener('click', function (e) {
            e.preventDefault();
            showWeekTab(this.getAttribute('data-week'));
        });
    });
    showSection('courses');
    function showWeekTab(week) {
        document.querySelectorAll('.week-section').forEach(div => {
            if (div.getAttribute('data-week') === week) {
                div.style.display = 'block';
            } else {
                div.style.display = 'none';
            }
        });
        document.querySelectorAll('.week-navbar a').forEach(a => {
            a.classList.toggle('active', a.getAttribute('data-week') === week);
        });
    }
    if (document.querySelector('.week-navbar a')) {
        showWeekTab('1-2');
    }
    document.querySelectorAll('.question-content').forEach(content => {
        content.classList.remove('open');
    });
});