<html>
<head>
	<meta charset="utf-8">
	<link href="https://fonts.googleapis.com/css?family=Pacifico" rel="stylesheet">
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.6.3/css/all.css" integrity="sha384-UHRtZLI+pbxtHCWp1t77Bi1L4ZtiqrqD80Kn4Z8NTSRyMA2Fd33n5dQ8lWUE00s/" crossorigin="anonymous">
<!--	<link rel="stylesheet" type="text/css" href="formStyle.css"> -->
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/css/bootstrap.min.css" integrity="sha384-GJzZqFGwb1QTTN6wy59ffF1BuGJpLSa9DkKMp0DgiMDm4iYMj70gZWKYbI706tWS" crossorigin="anonymous">

</head>
<body>
	<script>
	//se lance quand l'adresse change
	//elle met à jour la liste des adresses commençant par ce qui a été saisi par l'utilisateur
	function remplirListeDesAdresses()
	{
		alert("debut");
		//recup du debut du code postal de la commune
		var cp=document.getElementById('prodCp').value;
		if(cp.length >4)//à partir de 5 caractères
		{
			alert(">4");
			var dataListeAdresses=document.getElementById('listeVilles');
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
						alert("good");
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
							/*var leCp=document.getElementById("prodCp");
							leCp.setAttribute("value",tabJsonOptions.features[0].properties.postcode);
							var adresse=document.getElementById("prodAdressePostale");
							adresse.setAttribute("value",tabJsonOptions.features[0].properties.name);
							var laRue=document.getElementById("idRue");
							laRue.setAttribute("value",tabJsonOptions.features[0].properties.street);
							//latitude et longitude
							var laLatitude=document.getElementById("idLatitude");
							laLatitude.setAttribute("value",tabJsonOptions.features[0].geometry.coordinates[1]);
							var laLongitude=document.getElementById("idLongitude");
							laLongitude.setAttribute("value",tabJsonOptions.features[0].geometry.coordinates[0]);*/
							alert(tabJsonOptions.features[0].properties.city);
						}
						else
						{
							for(noLigne=0;noLigne<tabJsonOptions.features.length;noLigne++)
							{
								// Cree une nouvelle <option>.
								var nouvelleOption = document.createElement('option');
								// on renseigne la value de l'option avec le numéro du produit.
								nouvelleOption.value = tabJsonOptions.features[noLigne].properties.city;
								alert(nouvelleOption.value);
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
			var cp=document.getElementById('prodCp').value;
			//formation du texte de la requete
			var texteRequeteAjax='https://api-adresse.data.gouv.fr/search/?limit=5&q='+cp;
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
		<input required class="inputCss" type="text" name="prodCp" id="prodCp" placeholder="Code Postal" maxlength="5"  oninput="remplirListeDesAdresses()" >
		<br>
		<i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
	</p>
</div>

<div class="form">
	<p>
		<i class="fas fa-home"></i>
		<input readonly required list="listeVilles" class="inputCss" type="text" name="prodVille" id="prodVille" placeholder="Ville" maxlength="30" >
		<br>
		<i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
	</p>
	<datalist id="listeVilles"></datalist>
</div>

<div class="form">
	<p>
		<i class="fas fa-home"></i>
		<input required class="inputCss" type="text" name="prodAdressePostale" id="prodAdressePostale" placeholder="Adresse Postale Complète" maxlength="40" oninput="fonctionAdresse()">
		<br>
		<i class="fas fa-exclamation-circle" id="alerteNom" style="visibility: hidden;"></i>
	</p>

</div>


</body>
<script type="text/javascript" src="form.js"></script>
<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.6/umd/popper.min.js" integrity="sha384-wHAiFfRlMFy6i5SRaxvfOCifBUQy1xHdJ/yoi7FRNXMRBu5WHdZYu1hA6ZOblgut" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/js/bootstrap.min.js" integrity="sha384-B0UglyR+jN6CkvvICOB2joaf5I4l3gm9GU6Hc1og6Ls7i6U/mkkaduKaBhlAXv9k" crossorigin="anonymous"></script>
</html>
