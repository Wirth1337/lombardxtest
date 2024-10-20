<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the form data
    $name = htmlspecialchars($_POST['name']);
    $phone = htmlspecialchars($_POST['phone']);
    $email = htmlspecialchars($_POST['email']);
    $car_model = htmlspecialchars($_POST['car_model']);
    $year = htmlspecialchars($_POST['year']);
    $mileage = htmlspecialchars($_POST['mileage']);
    $value = htmlspecialchars($_POST['value']);
    $branch = htmlspecialchars($_POST['branch']);

    // Prepare the email details
    $to = "jgasiorek28@gmail.com"; // Replace with your email address
    $subject = "Nowa wycena samochodu od " . $name;
    $message = "
    <html>
    <head>
    <title>Wycena Samochodu</title>
    </head>
    <body>
    <p><strong>Imię i nazwisko:</strong> $name</p>
    <p><strong>Telefon:</strong> $phone</p>
    <p><strong>E-mail:</strong> $email</p>
    <p><strong>Marka i model samochodu:</strong> $car_model</p>
    <p><strong>Rok produkcji:</strong> $year</p>
    <p><strong>Ilość przejechanych km:</strong> $mileage</p>
    <p><strong>Kwota:</strong> $value</p>
    <p><strong>Oddział:</strong> $branch</p>
    </body>
    </html>
    ";

    // Set the headers
    $headers = "MIME-Version: 1.0" . "\r\n";
    $headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";
    $headers .= "From: <$email>" . "\r\n";

    // Send the email
    if (mail($to, $subject, $message, $headers)) {
        echo "Twoja wiadomość została wysłana pomyślnie.";
    } else {
        echo "Wystąpił błąd podczas wysyłania wiadomości.";
    }
}
?>
