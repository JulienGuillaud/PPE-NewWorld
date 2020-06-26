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
      header ('location: index.php');
      echo "<a href=\"deconnection.php\" class=\"navItem\"><b>DECONNECTION</b></a>";
      echo "<a href=\"gestionProducteurs.php\" class=\"navItem\"><b>GESTION</b></a>";
    }
    ?>
    <a href="index.php" class="navItem"><b>ACCUEIL</b></a>
  </div>
  <h1 class="h1Titre" style="margin-bottom:20px;">Inscription Producteur</h1>
  <form method="POST" action="recapForm.php">

    <div class="row justify-content-md-center">
      <div class="col-3">
        <div class="form">
          <p>
            <i class="fas fa-address-card"></i>
            <input class="inputCss" type="text" id="prodNom" name="prodNom" placeholder="Votre Nom" oninput="toutVerif()" maxlength="30">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"> Nom non valide</i>
          </p>
          <p>
            <i class="fas fa-address-card"></i>
            <input class="inputCss" type="text" id="prodPrenom" name="prodPrenom" placeholder="Votre Prénom" oninput="toutVerif()" maxlength="30">
            <br>
            <i class="fas fa-exclamation-circle" id="alertePrenom" style="visibility: hidden;"> Prenom non valide</i>
          </p>
          <p>
            <i class="fas fa-phone"></i>
            <input class="inputCss" type="tel" id="prodTelFixe" name="prodTelFixe" placeholder="tel fix ex:00 00 00 00 00" oninput="toutVerif()" maxlength="10">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteTelFix" style="visibility: hidden;"> Tel non valide</i>
          </p>
          <p>
            <i class="fas fa-phone"></i>
            <input class="inputCss" type="tel" id="prodTelPortable" name="prodTelPortable" placeholder="tel portable ex:00 00 00 00 00" oninput="toutVerif()"  maxlength="10">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteTelPortable" style="visibility: hidden;"> Tel non valide</i>
          </p>

        </div>
      </div>
      <div class="col-">
        <div class="form">
          <p class="checkbox activite activite"><i class="fas fa-tasks"></i> Activité :</p>
        </div>
        <div class="form">
          <div class="check">
            <input type="checkbox" name="fruits">
            <label class="checkbox" for="fruits">Fruits</label>
            <br>
            <input type="checkbox" name="legumes">
            <label class="checkbox" for="legumes">Legumes</label>
            <br>
            <input type="checkbox" name="viandes">
            <label class="checkbox" for="viandes">Viandes</label>
            <br>
            <input type="checkbox" name="laitages">
            <label class="checkbox" for="laitages">Laitages</label>
            <br>
            <input type="checkbox" name="services">
            <label class="checkbox" for="services">Services</label>
            <br>
            <input type="checkbox" name="autre" id="autre" onclick="autreAppel()">
            <label class="checkbox" for="autre" onclick="toutVerif()">Autre</label>
            <br>
            <input type="text" name="autreInput" id="autreInputId" style="visibility: hidden;" placeholder="Entrez votre domaine d'activité." maxlength="30">
          </div>
        </div>
      </div>
      <div class="col-3">
        <div class="form">
          <p>
            <i class="fas fa-home"></i>
            <input class="inputCss" type="text" name="prodCp" id="prodCp" placeholder="Code Postal" maxlength="5">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
          </p>
        </div>
        <div class="form">
          <p>
            <i class="fas fa-home"></i>
            <input class="inputCss" type="text" name="prodVille" id="prodVille" placeholder="Ville" maxlength="30">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
          </p>
        </div>
        <div class="form">
          <p>
            <i class="fas fa-home"></i>
            <input class="inputCss" type="text" name="prodAdressePostale" id="prodAdressePostale" placeholder="Adresse Postale Complète" maxlength="40" oninput="fonctionAdresse()">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
          </p>
        </div>
        <div class="form">
          <p>
            <i class="fas fa-industry"></i>
            <input class="inputCss" type="text" name="prodSiretSiren" id="prodSiretSiren" placeholder="n° Siret" maxlength="14">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
          </p>
        </div>

        <div class="form">
          <p>
            <i class="fas fa-industry"></i>
            <input class="inputCss" type="text" name="nomEntreprise" id="nomEntreprise" placeholder="Nom Entreprise" maxlength="30">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
          </p>
        </div>


        <div class="form">
          <p>
            <i class="fas fa-lock prefix grey-text"></i>
            <input class="inputCss" type="password" name="prodMotDePasse" id="prodMotDePasse" placeholder="Votre Mot de passe" oninput="toutVerif()" maxlength="60">
            <!--<br>
            <img id="imgMdp">-->
            <br>
            <i class="fas fa-exclamation-circle" name="alertMdp" id="alertMdp" style="visibility: hidden;"></i>
            <i class="fas fa-at" id="alertSpeciaux"><i class="" id="alertA"><b> A </b><i class="" id="alertChar">10char <i class="fas fa-sort-numeric-up" id="alertNum"></i></i></i></i>

          </p>
          <p>
            <i class="fas fa-lock prefix grey-text"></i>
            <input class="inputCss" type="password" name="prodConfirmMotDePasse" id="prodConfirmMotDePasse" placeholder="Confirmation Mot de passe" oninput="toutVerif()" maxlength="60">
            <br>
            <div style="">
              <i class="fas fa-exclamation-circle" id="alerteMdpDifferents" style="visibility: hidden;"> Mdp differents</i>
            </div>
          </p>

        </div>
        <div class="form">
          <p>
            <input class="boutonEnvoyer" id="boutonEnvoyer" type="submit" style="visibility: hidden;" value="S'inscrire">
          </p>
        </div>
      </div>
      <div class="col-3">
        <p>
          <i class="fas fa-user prefix grey-text"></i>
          <input class="inputCss" type="text" name="prodLogin" id="prodLogin" placeholder="Login"  oninput="toutVerif()"  maxlength="30">
          <br>
          <i class="fas fa-exclamation-circle" id="alerteLogin" style="visibility: hidden;"> Login non valide</i>
        </p>
        <p>
          <i class="fas fa-envelope prefix grey-text"></i>
          <input class="inputCss" type="email" name="prodEmail" id="prodEmail" placeholder="Votre Email" oninput="toutVerif()" maxlength="60">
          <br>
          <i class="fas fa-exclamation-circle" id="alerteEmail" style="visibility: hidden;"> Email non valide</i>
        </p>
        <p>
          <i class="fas fa-envelope prefix grey-text"></i>
          <input class="inputCss" type="email" name="prodConfirmEmail" id="prodConfirmEmail" placeholder="Confirmation email" oninput="toutVerif()" maxlength="60">
          <br>
          <i class="fas fa-exclamation-circle" id="alerteEmailDifferentes" style="visibility: hidden;"> Email differente</i>
        </p>
      </div>
    </div>



  </form>
</body>
<script type="text/javascript" src="form.js"></script>
<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.6/umd/popper.min.js" integrity="sha384-wHAiFfRlMFy6i5SRaxvfOCifBUQy1xHdJ/yoi7FRNXMRBu5WHdZYu1hA6ZOblgut" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/js/bootstrap.min.js" integrity="sha384-B0UglyR+jN6CkvvICOB2joaf5I4l3gm9GU6Hc1og6Ls7i6U/mkkaduKaBhlAXv9k" crossorigin="anonymous"></script>
</html>
