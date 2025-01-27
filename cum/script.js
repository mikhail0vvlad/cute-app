const text = document.getElementById('text');
const gif = document.getElementById('gif');

const yesButton = document.getElementById('yesButton');
const noButton = document.getElementById('noButton');

yesButton.addEventListener('click', () => {
	text.innerHTML = "Открой дверь о_0";
	gif.src = 'https://i.pinimg.com/originals/bc/0a/ff/bc0affc97f7ea9649ad19cf29f913901.gif';
	
	yesButton.style.display = 'none';
	noButton.style.display = 'none';
});

noButton.addEventListener('mouseover', () => {
	const noButtonRect = noButton.getBoundingClientRect();

	const maxX = window.innerWidth - noButtonRect.width;
    const maxY = window.innerHeight - noButtonRect.height;

    const randomX = Math.floor(Math.random() * maxX);
    const randomY = Math.floor(Math.random() * maxY);

    noButton.style.left = randomX + "px";
    noButton.style.top = randomY + "px";
});