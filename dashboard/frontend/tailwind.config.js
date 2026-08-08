/** @type {import('tailwindcss').Config} */
export default {
  content: ["./index.html", "./src/**/*.{js,jsx}"],
  theme: {
    extend: {
      colors: {
        healthy: "#22c55e",
        warning: "#eab308",
        fault: "#ef4444",
      },
    },
  },
  plugins: [],
};
