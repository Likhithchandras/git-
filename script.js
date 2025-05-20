const questions = [
  {
    question: "What is the capital of Germany?",
    options: ["Berlin", "Paris", "Madrid", "Rome"],
    correct: 0,
    hint: "It starts with a 'B'."
  },
  {
    question: "What is 2 + 2 * 2?",
    options: ["6", "8", "4", "10"],
    correct: 0,
    hint: "Follow the order of operations (PEMDAS)."
  },
  {
    question: "Which language runs in a web browser?",
    options: ["Java", "C", "Python", "JavaScript"],
    correct: 3,
    hint: "It's often confused with Java."
  }
];

let currentIndex = 0;
let score = 0;
let timer;
let timeLeft = 15;

function loadQuestion() {
  clearInterval(timer);
  timeLeft = 15;
  document.getElementById('time').textContent = timeLeft;
  startTimer();

  const q = questions[currentIndex];
  document.getElementById("question").textContent = q.question;
  const form = document.getElementById("options-form");
  const feedback = document.getElementById("feedback");
  const hint = document.getElementById("hint");

  feedback.textContent = "";
  hint.textContent = "";

  form.innerHTML = "";

  q.options.forEach((opt, index) => {
    const label = document.createElement("label");
    label.innerHTML = `
      <input type="radio" name="option" value="${index}" />
      ${opt}
    `;
    form.appendChild(label);
  });

  updateProgress();
}

function startTimer() {
  timer = setInterval(() => {
    timeLeft--;
    document.getElementById("time").textContent = timeLeft;
    if (timeLeft === 0) {
      clearInterval(timer);
      submitAnswer(true);
    }
  }, 1000);
}

function submitAnswer(timeout = false) {
  clearInterval(timer);

  const selected = document.querySelector("input[name='option']:checked");
  const feedback = document.getElementById("feedback");
  const hint = document.getElementById("hint");

  if (!selected && !timeout) {
    feedback.textContent = "Please select an answer!";
    return;
  }

  const answerIndex = timeout ? -1 : parseInt(selected.value);
  const correctIndex = questions[currentIndex].correct;

  if (answerIndex === correctIndex) {
    score++;
    feedback.textContent = "Correct!";
    feedback.style.color = "green";
  } else {
    feedback.textContent = timeout ? "Time's up!" : "Wrong!";
    feedback.style.color = "red";
  }

  setTimeout(() => {
    currentIndex++;
    if (currentIndex < questions.length) {
      loadQuestion();
    } else {
      showResult();
    }
  }, 1500);
}

function showHint() {
  document.getElementById("hint").textContent = "Hint: " + questions[currentIndex].hint;
}

function updateProgress() {
  const percent = ((currentIndex) / questions.length) * 100;
  document.getElementById("progress").style.width = percent + "%";
}

function showResult() {
  document.getElementById("quiz").classList.add("hidden");
  document.getElementById("result").classList.remove("hidden");
  document.getElementById("score").textContent = ${score} / ${questions.length};

  const highScore = localStorage.getItem("highScore") || 0;
  if (score > highScore) {
    localStorage.setItem("highScore", score);
  }
  document.getElementById("high-score").textContent = localStorage.getItem("highScore");
}

function restartQuiz() {
  currentIndex = 0;
  score = 0;
  document.getElementById("quiz").classList.remove("hidden");
  document.getElementById("result").classList.add("hidden");
  loadQuestion();
}

// Start quiz
loadQuestion();