document.addEventListener("DOMContentLoaded", function () {
  const contactForm = document.getElementById("contact-form");
  const emailTemplateId = document.getElementById("email-template").value;
  const thankYouMessage = document.getElementById("thank-you-message");
  let YOUR_EMAIL_PUBLIC_KEY = "LSnSaPz_1rUgYu8p0";
  // Replace 'YOUR_EMAIL_PUBLIC_KEY' with your actual EmailJS public key
  emailjs.init(YOUR_EMAIL_PUBLIC_KEY);

  contactForm.addEventListener("submit", function (event) {
    event.preventDefault(); // Prevent the default form submission

    // Get the form data
    const formData = new FormData(contactForm);
    // Send an email using EmailJS
    emailjs
      .send("service_56x4i3o", emailTemplateId, {
        name: formData.get("name"),
        email: formData.get("email"),
        message: formData.get("message"),
      })
      .then(
        function (response) {
          console.log("Email sent successfully:", response);
          // Show a thank you message and hide the form
          contactForm.style.display = "none";
          thankYouMessage.style.display = "block";
        },
        function (error) {
          console.error("Email send error:", error);
        }
      );
  });
});
