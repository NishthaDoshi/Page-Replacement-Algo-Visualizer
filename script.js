let currentAlgorithm = 'FIFO';
let cacheSize = 3;
let cache = [];
let sequence = [];
let hits = 0;
let misses = 0;

function setAlgorithm(algo) {
    currentAlgorithm = algo;
    resetCache();
    
    // Update UI
    document.querySelectorAll('.algorithm-select .btn').forEach(btn => {
        btn.classList.remove('active');
    });
    event.target.classList.add('active');
}

function updateCacheSize(size) {
    cacheSize = parseInt(size);
    if (isNaN(cacheSize) || cacheSize < 1) cacheSize = 1;
    if (cacheSize > 10) cacheSize = 10;
    
    // Trim cache if new size is smaller
    if (cache.length > cacheSize) {
        cache = cache.slice(-cacheSize);
    }
    
    updateCacheDisplay();
}

function resetCache() {
    cache = [];
    sequence = [];
    hits = 0;
    misses = 0;
    updateCacheDisplay();
    updateStats();
    updateSequence();
}

function addValue() {
    const input = document.getElementById('inputValue');
    const value = input.value.trim();
    
    if (value) {
        sequence.push(value);
        processCache(value);
        input.value = '';
        updateSequence();
    }
}

function processCache(value) {
    const isHit = cache.includes(value);
    
    if (isHit) {
        hits++;
        if (currentAlgorithm === 'LRU') {
            // Move to end (most recently used)
            cache = cache.filter(item => item !== value);
            cache.push(value);
        }
    } else {
        misses++;
        if (cache.length >= cacheSize) {
            // Remove based on algorithm
            cache.shift(); // For both FIFO and LRU, remove first element
        }
        cache.push(value);
    }
    
    updateCacheDisplay();
    updateStats();
}

function updateCacheDisplay() {
    const container = document.getElementById('cacheSlots');
    container.innerHTML = '';
    
    for (let i = 0; i < cacheSize; i++) {
        const slot = document.createElement('div');
        slot.className = 'cache-slot';
        slot.textContent = cache[i] || '-';
        container.appendChild(slot);
    }
}

function updateStats() {
    const total = hits + misses;
    const hitRate = total ? ((hits / total) * 100).toFixed(1) : 0;
    const missRate = total ? ((misses / total) * 100).toFixed(1) : 0;
    
    document.getElementById('hits').textContent = hits;
    document.getElementById('misses').textContent = misses;
    document.getElementById('hitRate').textContent = `Rate: ${hitRate}%`;
    document.getElementById('missRate').textContent = `Rate: ${missRate}%`;
}

function updateSequence() {
    const container = document.getElementById('sequence');
    container.innerHTML = '';
    
    sequence.forEach(value => {
        const item = document.createElement('div');
        item.className = 'sequence-item';
        item.textContent = value;
        container.appendChild(item);
    });
}

// Initialize the display
updateCacheDisplay();