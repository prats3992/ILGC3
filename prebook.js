document.addEventListener("DOMContentLoaded", function () {
    const contactForm = document.getElementById("myForm");
    const emailTemplateId = document.getElementById("email-template").value;
    const successMessage = document.getElementById("successMessage");
    let YOUR_EMAIL_PUBLIC_KEY = "LSnSaPz_1rUgYu8p0";
    // Replace 'YOUR_EMAIL_PUBLIC_KEY' with your actual EmailJS public key
    emailjs.init(YOUR_EMAIL_PUBLIC_KEY);
  
    contactForm.addEventListener("submit", function (event) {
      event.preventDefault(); // Prevent the default form submission
  
      // Get the form data
      const formData = new FormData(contactForm);
      const choice = formData.get("choice");
      // Send an email using EmailJS
      emailjs
        .send("service_56x4i3o", emailTemplateId, {
          name: formData.get("name"),
          email: formData.get("email"),
          choice: choice,
          time: choice === "morning" ? formData.get("timeSelectionMorn") : formData.get("timeSelectionEve"),
        })
        .then(
          function (response) {
            console.log("Email sent successfully:", response);
            // Hide the form
            contactForm.style.display = "none";
            // Show the success message
            successMessage.style.display = "block";
          },
          function (error) {
            console.error("Email send error:", error);
          }
        );
    });
  });