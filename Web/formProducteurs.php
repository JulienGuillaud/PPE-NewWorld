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


  </script>
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
            <input required class="inputCss" type="text" id="prodNom" name="prodNom" placeholder="Votre Nom" oninput="toutVerif()" maxlength="30">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"> Nom non valide</i>
          </p>
          <p>
            <i class="fas fa-address-card"></i>
            <input required class="inputCss" type="text" id="prodPrenom" name="prodPrenom" placeholder="Votre Prénom" oninput="toutVerif()" maxlength="30">
            <br>
            <i class="fas fa-exclamation-circle" id="alertePrenom" style="visibility: hidden;"> Prenom non valide</i>
          </p>
          <p>
            <i class="fas fa-phone"></i>
            <input required class="inputCss" type="tel" id="prodTelFixe" name="prodTelFixe" placeholder="tel fix ex:00 00 00 00 00" oninput="toutVerif()" maxlength="10">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteTelFix" style="visibility: hidden;"> Tel non valide</i>
          </p>
          <p>
            <i class="fas fa-phone"></i>
            <input required class="inputCss" type="tel" id="prodTelPortable" name="prodTelPortable" placeholder="tel portable ex:00 00 00 00 00" oninput="toutVerif()"  maxlength="10">
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
        <script>
//cette fonction n'est plus utilisée j'ai mis un autocomplete à la place
//se lance quand l'adresse change
//elle met à jour la liste des adresses commençant par ce qui a été saisi par l'utilisateur
function remplirListeDesAdresses()
{
  //recup du debut du code postal de la commune
  var debutAdresse=document.getElementById('prodAdressePostale').value;
  if(debutAdresse.length >10)//à partir de 10 caractères
  {
	  var dataListeAdresses=document.getElementById('listeDesAdresses');
	  //j'efface toutes les options de la datalist
	  //essais
	  $(dataListeAdresses).empty();
	  var noAdresse;
	  var nbAdresses=dataListeAdresses.length;
	  for (noAdresse = 0; noAdresse < nbAdresses; noAdresse++)
	  {
	    dataListeAdresses.remove(0);
	  }
	  //je cree ma requete vers le serveur data.gouv.fr
	  var request = new XMLHttpRequest();
	  // prise en charge des chgts d'état de la requete
	  request.onreadystatechange = function(response)
	  {
	    if (request.readyState === 4)
	    {
	      if (request.status === 200)
	      {
			// j'obtient la reponse au format json et l'analyse on obtient un tableau
			var tabJsonOptions = JSON.parse(request.responseText);
			//alert (tabJsonOptions.features[0].properties.label);
			//alert(request.responseText);
			// pour chaque ligne du tableau.
			var noLigne;
			if(tabJsonOptions.features.length==1)
			{
				//remplir les zones de saisie cpostal et ville
				var laVille=document.getElementById("prodVille");
				laVille.setAttribute("value",tabJsonOptions.features[0].properties.city);
				var leCp=document.getElementById("prodCp");
				leCp.setAttribute("value",tabJsonOptions.features[0].properties.postcode);
      //  var adresse=document.getElementById("prodAdressePostale");
			//	adresse.setAttribute("value",tabJsonOptions.features[0].properties.name);
				/*var laRue=document.getElementById("idRue");
				laRue.setAttribute("value",tabJsonOptions.features[0].properties.street);
				//latitude et longitude
				var laLatitude=document.getElementById("idLatitude");
				laLatitude.setAttribute("value",tabJsonOptions.features[0].geometry.coordinates[1]);
				var laLongitude=document.getElementById("idLongitude");
				laLongitude.setAttribute("value",tabJsonOptions.features[0].geometry.coordinates[0]);*/
			}
			else
			{
				for(noLigne=0;noLigne<tabJsonOptions.features.length;noLigne++)
				{
					// Cree une nouvelle <option>.
					var nouvelleOption = document.createElement('option');
					// on renseigne la value de l'option avec le numéro du produit.
					nouvelleOption.value = tabJsonOptions.features[noLigne].properties.label;
					//on affiche aussi le codePostal et la commune
					nouvelleOption.text=nouvelleOption.value;
					// ajout  de l'<option> en tant qu'enfant de la liste de selection des produits.
					dataListeAdresses.appendChild(nouvelleOption);
					//alert('option ajoutee'+tabJsonOptions.features[noLigne].properties.label);
				}
			}
	      }
	       else
	       {
		  // An error occured :(
		  alert("Couldn't load datalist options :(");
	       }
	    }
	  };
	  //recup du debut du code postal de la commune
	  var debutAdresse=document.getElementById('prodAdressePostale').value;
	  //formation du texte de la requete
	  var texteRequeteAjax='https://api-adresse.data.gouv.fr/search/?limit=10&q='+debutAdresse;
	  //je l'ouvre
	  request.open('GET', texteRequeteAjax, true);
	  //et l'envoie
	  request.send();
  }//fin du si + de 5 caractères ont été saisi
}
</script>
        <div class="form">
          <p>
            <i class="fas fa-home"></i>
            <input required list="listeDesAdresses" class="inputCss" type="text" name="prodAdressePostale" id="prodAdressePostale" oninput="remplirListeDesAdresses()" placeholder="Adresse Postale Complète" maxlength="40" oninput="fonctionAdresse()">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
          </p>
          <datalist id="listeDesAdresses"></datalist>
        </div>

<!--<script language="javascript">
	//auto complément de l'adresse ville et code postal
	$("#prodAdressePostale").autocomplete({
	source: function (request, response) {
		$.ajax({
			url: "https://api-adresse.data.gouv.fr/search/?limit=5",
			data: { q: request.term },
			dataType: "json",
			success: function (data) {
				response($.map(data.features, function (item) {
					return { label: item.properties.label, postcode: item.properties.postcode,city: item.properties.city, value: item.properties.label, street: item.properties.street, name: item.properties.name, latitude: item.geometry.coordinates[1],longitude: item.geometry.coordinates[0]};
				}));
			}
		});
	},
	select: function(event, ui) {
		$('#idCP').val(ui.item.postcode);
		$('#idVille').val(ui.item.city);
		if(ui.item.street)
		{
			$('#idRue').val(ui.item.street);
			//$('#prodAdressePostale').val(ui.item.street);
		}
	    	else
		{
			$('#idRue').val(ui.item.name);
			//$('#prodAdressePostale').val(ui.item.name);
		}
	    	$("#idLatitude").val(ui.item.latitude);
	    	$("#idLongitude").val(ui.item.longitude);
	}
});
</script>
-->
        <div class="form">
          <p>
            <i class="fas fa-home"></i>
            <input required class="inputCss" type="text" name="prodCp" id="prodCp" placeholder="" maxlength="5" oninput="fonctionCP()" readonly>
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
          </p>
        </div>
        <div class="form">
          <p>
            <i class="fas fa-home"></i>
            <input required class="inputCss" type="text" name="prodVille" id="prodVille" placeholder="" maxlength="30" readonly>
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
          </p>
        </div>
        <div class="form">
          <p>
            <i class="fas fa-industry"></i>
            <input required class="inputCss" type="text" name="prodSiretSiren" id="prodSiretSiren" placeholder="n° Siret" maxlength="14">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
          </p>
        </div>

        <div class="form">
          <p>
            <i class="fas fa-industry"></i>
            <input required class="inputCss" type="text" name="nomEntreprise" id="nomEntreprise" placeholder="Nom Entreprise" maxlength="30">
            <br>
            <i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
          </p>
        </div>


        <div class="form">
          <p>
            <i class="fas fa-lock prefix grey-text"></i>
            <input required class="inputCss" type="password" name="prodMotDePasse" id="prodMotDePasse" placeholder="Votre Mot de passe" oninput="toutVerif()" maxlength="60">
            <!--<br>
            <img id="imgMdp">-->
            <br>
            <i class="fas fa-exclamation-circle" name="alertMdp" id="alertMdp" style="visibility: hidden;"></i>
            <i class="fas fa-at" id="alertSpeciaux"><i class="" id="alertA"><b> A </b><i class="" id="alertChar">10char <i class="fas fa-sort-numeric-up" id="alertNum"></i></i></i></i>

          </p>
          <p>
            <i class="fas fa-lock prefix grey-text"></i>
            <input required class="inputCss" type="password" name="prodConfirmMotDePasse" id="prodConfirmMotDePasse" placeholder="Confirmation Mot de passe" oninput="toutVerif()" maxlength="60">
            <br>
            <div style="">
              <i class="fas fa-exclamation-circle" id="alerteMdpDifferents" style="visibility: hidden;"> Mdp differents</i>
            </div>
          </p>

        </div>
        <div class="form">
          <p>
            <input required class="boutonEnvoyer" id="boutonEnvoyer" type="submit" style="visibility: hidden;" value="S'inscrire">
          </p>
        </div>
      </div>
      <div class="col-3">
        <p>
          <i class="fas fa-user prefix grey-text"></i>
          <input required class="inputCss" type="text" name="prodLogin" id="prodLogin" placeholder="Login"  oninput="toutVerif()"  maxlength="30">
          <br>
          <i class="fas fa-exclamation-circle" id="alerteLogin" style="visibility: hidden;"> Login non valide</i>
        </p>
        <p>
          <i class="fas fa-envelope prefix grey-text"></i>
          <input required class="inputCss" type="email" name="prodEmail" id="prodEmail" placeholder="Votre Email" oninput="toutVerif()" maxlength="60">
          <br>
          <i class="fas fa-exclamation-circle" id="alerteEmail" style="visibility: hidden;"> Email non valide</i>
        </p>
        <p>
          <i class="fas fa-envelope prefix grey-text"></i>
          <input required class="inputCss" type="email" name="prodConfirmEmail" id="prodConfirmEmail" placeholder="Confirmation email" oninput="toutVerif()" maxlength="60">
          <br>
          <i class="fas fa-exclamation-circle" id="alerteEmailDifferentes" style="visibility: hidden;"> Email differente</i>
        </p>
      </div>
    </div>
<div id="div1">
</div>


  </form>
</body>
<script type="text/javascript" src="form.js"></script>
<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.6/umd/popper.min.js" integrity="sha384-wHAiFfRlMFy6i5SRaxvfOCifBUQy1xHdJ/yoi7FRNXMRBu5WHdZYu1hA6ZOblgut" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/js/bootstrap.min.js" integrity="sha384-B0UglyR+jN6CkvvICOB2joaf5I4l3gm9GU6Hc1og6Ls7i6U/mkkaduKaBhlAXv9k" crossorigin="anonymous"></script>
</html>
