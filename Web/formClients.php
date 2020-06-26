<?php
session_start();
include('connect.php');
?>
<html>
<head>
  <title>Formulaire d'inscription</title>
  <meta charset="utf-8">
  <link href="https://fonts.googleapis.com/css?family=Pacifico" rel="stylesheet">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.6.3/css/all.css" integrity="sha384-UHRtZLI+pbxtHCWp1t77Bi1L4ZtiqrqD80Kn4Z8NTSRyMA2Fd33n5dQ8lWUE00s/" crossorigin="anonymous">
  <link rel="stylesheet" type="text/css" href="formStyle.css">
  <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/css/bootstrap.min.css" integrity="sha384-GJzZqFGwb1QTTN6wy59ffF1BuGJpLSa9DkKMp0DgiMDm4iYMj70gZWKYbI706tWS" crossorigin="anonymous">
</head>
<body>
	<div class="header">
		<a href="index.php" class="logo"><b>NEW-WORLD</b></a>
		<a href="index.php" class="navItem"><b>CONTACT</b></a>
<?php
if (!isset($_SESSION['prodLogin']) || !isset($_SESSION['cliLogin']))
{
	echo "<a href=\"connection.php\" class=\"navItem\"><b>CONNECTION</b></a>";
	echo "<a href=\"inscription.php\" class=\"navItem active\"><b>INSCRIPTION</b></a>";
}
else
{
  if (isset($_SESSION['cliLogin']))
  {
    echo "<a href=\"deconnection.php\" class=\"navItem\"><b>DECONNECTION</b></a>";
    echo "<a href=\"profileClient.php\" class=\"navItem\"><b>DECONNECTION</b></a>";
  }
	header ('location: index.php');
	echo "<a href=\"deconnection.php\" class=\"navItem\"><b>DECONNECTION</b></a>";
	echo "<a href=\"gestionProducteurs.php\" class=\"navItem\"><b>GESTION</b></a>";
}
?>
		<a href="index.php" class="navItem"><b>ACCUEIL</b></a>
	</div>
<form method="POST" action="recapForm.php">
  <h1 class="h1Titre">Inscription Client</h1>
  <div class="center-block form">
               <p>
                 <i class="fas fa-address-card"></i>
                 <input class="inputCss" type="text" id="cliNom" name="cliNom" placeholder="Votre Nom" oninput="toutVerif()" maxlength="30">
                 <br>
                 <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"> Nom non valide</i>
               </p>
               <p>
                 <i class="fas fa-address-card"></i>
                 <input class="inputCss" type="text" id="cliPrenom" name="cliPrenom" placeholder="Votre Prénom" oninput="toutVerif()" maxlength="30">
                 <br>
                 <i class="fas fa-exclamation-circle" id="alertePrenom" style="visibility: hidden;"> Prenom non valide</i>
               </p>
               <p>
                 <i class="fas fa-phone"></i>
                 <input class="inputCss" type="tel" id="cliTelFixe" name="cliTelFixe" placeholder="tel fix ex:00 00 00 00 00" oninput="toutVerif()" maxlength="10">
                 <br>
                 <i class="fas fa-exclamation-circle" id="alerteTelFix" style="visibility: hidden;"> Tel non valide</i>
               </p>
               <p>
                 <i class="fas fa-phone"></i>
                 <input class="inputCss" type="tel" id="cliTelPortable" name="cliTelPortable" placeholder="tel portable ex:00 00 00 00 00" oninput="toutVerif()"  maxlength="10">
                 <br>
                 <i class="fas fa-exclamation-circle" id="alerteTelPortable" style="visibility: hidden;"> Tel non valide</i>
               </p>
  </div>

  <div class="form">
                <p>
                  <i class="fas fa-home"></i>
                  <input class="inputCss" type="text" name="cliAdressePostale" id="cliAdressePostale" placeholder="Adresse Postale Complète" maxlength="40" oninput="fonctionAdresse()">
                </p>
  </div>
  <div class="form">
                <p>
                  <i class="fas fa-home"></i>
                  <input class="inputCss" type="text" name="cliCp" id="cliCp" placeholder="Code Postal" maxlength="5">
                </p>
  </div>
  <div class="form">
                <p>
                  <i class="fas fa-home"></i>
                  <input class="inputCss" type="text" name="cliVille" id="cliVille" placeholder="Ville" maxlength="30">
                </p>
  </div>
  <div class="form">
                <p>
                  <i class="fas fa-industry"></i>
                  <input class="inputCss" type="text" name="cliSiretSiren" id="cliSiretSiren" placeholder="n° Siret" maxlength="14">
                </p>
  </div>

  <div class="form">
                <p>
                  <i class="fas fa-industry"></i>
                  <input class="inputCss" type="text" name="nomEntreprise" id="nomEntreprise" placeholder="Nom Entreprise" maxlength="30">
                </p>
  </div>


  <div class="form">
               <p>
                  <i class="fas fa-user prefix grey-text"></i>
                 <input class="inputCss" type="text" name="cliLogin" id="cliLogin" placeholder="Login" maxlength="30">
               </p>
  </div>
  <div class="form">
                <p>
                  <i class="fas fa-envelope prefix grey-text"></i>
                  <input class="inputCss" type="email" name="cliEmail" id="cliEmail" placeholder="Votre Email" oninput="toutVerif()" maxlength="60">
                  <br>
                  <i class="fas fa-exclamation-circle" id="alerteEmail" style="visibility: hidden;"> Email non valide</i>
                </p>
                <p>
                  <i class="fas fa-envelope prefix grey-text"></i>
                  <input class="inputCss" type="email" name="cliConfirmEmail" id="cliConfirmEmail" placeholder="Confirmation email" oninput="toutVerif()" maxlength="60">
                  <br>
                  <i class="fas fa-exclamation-circle" id="alerteEmailDifferentes" style="visibility: hidden;"> Email differente</i>
                </p>
                <p>
                  <i class="fas fa-lock prefix grey-text"></i>
                  <input class="inputCss" type="password" name="cliMotDePasse" id="cliMotDePasse" placeholder="Votre Mot de passe" oninput="toutVerif()" maxlength="60">
                  <br>
                  <img id="imgMdp">
                  <br>
                  <i class="fas fa-exclamation-circle" name="alertMdp" id="alertMdp" style="visibility: hidden;"></i>
                  <i class="fas fa-at" id="alertSpeciaux"><i class="" id="alertA"><b> A </b><i class="" id="alertChar">10char <i class="fas fa-sort-numeric-up" id="alertNum"></i></i></i></i>

                </p>
               <p>
                 <i class="fas fa-lock prefix grey-text"></i>
                 <input class="inputCss" type="password" name="cliConfirmMotDePasse" id="cliConfirmMotDePasse" placeholder="Confirmation Mot de passe" oninput="toutVerif()" maxlength="60">
                 <br>
                 <i class="fas fa-exclamation-circle" id="alerteMdpDifferents" style="visibility: hidden;"> Mdp differents</i>
               </p>

  </div>
  <div class="form">
      <p>
        <input class="boutonEnvoyer" id="boutonEnvoyer" type="submit" style="visibility: hidden;" value="S'inscrire">
      </p>
  </div>
</form>
  </body>
    <script type="text/javascript" src="form.js"></script>
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.6/umd/popper.min.js" integrity="sha384-wHAiFfRlMFy6i5SRaxvfOCifBUQy1xHdJ/yoi7FRNXMRBu5WHdZYu1hA6ZOblgut" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/js/bootstrap.min.js" integrity="sha384-B0UglyR+jN6CkvvICOB2joaf5I4l3gm9GU6Hc1og6Ls7i6U/mkkaduKaBhlAXv9k" crossorigin="anonymous"></script>
</html>
