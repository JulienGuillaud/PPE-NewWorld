var fonctionVerifEmailOk=0
var fonctionVerifConfirmEmailOk=0
var coche=false
var difficulteMdp=0;
var boutonEnvoyer=document.getElementById('boutonEnvoyer');
var verifBoutonEmail=false;
var verifBoutonverifNom=false;
var verifBoutonverifPrenom=false;
var verifBoutonTelFix=false;
var verifBoutonTelPortable=false;
var verifBoutonMdp=false;
var verifBoutonConfirmMdp=false;


function autreAppel()
{
	toutVerif();
	fonctionAutre();
}

function toutVerif()
{
	fonctionVerifEmail();
	fonctionVerifConfirmEmail();
	fonctionVerifNom();
	fonctionVerifPrenom();
	fonctionVerifTelFix();
	fonctionVerifTelPortable();
	fonctionMdp();
	fonctionConfirmMdp();
	verifBouton();
	fonctionVerifLogin();
}

function fonctionCP()
{

	const req = new XMLHttpRequest();
	cp=document.getElementById('prodCp');
	if(cp.value.length>=5)
	{
		querry='http://api-adresse.data.gouv.fr/search/?q='+cp.value+'&limit=15&postcode='+cp.value;
		req.open('GET', querry, false);
		req.send(null);
		if (req.status === 200) {
			console.log("Réponse reçue: %s", req.responseText);
			var newP = document.createElement(newP);
			var pContent = document.createTextNode(req.responseText);
			newP.appendChild(pContent);
			var currentDiv=document.getElementById('div1');

		} else {
			console.log("Status de la réponse: %d (%s)", req.status, req.statusText);
		}
	}
}

function fonctionVerifLogin()
{
	var login=document.getElementById("prodLogin");
	var alerte=document.getElementById("alerteLogin");

	if (login.value.length<2)
	{
		alerte.setAttribute('style', 'visibility: visible;');
		login.style.borderBottom = "solid red 3px";
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
	}
	else
	{
		alerte.setAttribute('style', 'visibility: hidden;');
		login.style.borderBottom = "solid green 3px";
		verifBoutonverifNom=true;
		verifBouton();
	}
}

function fonctionVerifEmail()
{
	var email=document.getElementById("prodEmail");
	var alerteEmail=document.getElementById("alerteEmail");


	if (prodEmail.value.indexOf("@")!= -1 && prodEmail.value.indexOf(".")!= -1)
	{
		alerteEmail.setAttribute('style', 'visibility: hidden;');
		email.style.borderBottom = "solid green 3px";

	}
	else
	{
		alerteEmail.setAttribute('style', 'visibility: visible;');
		email.style.borderBottom = "solid red 3px";
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
	}
}

function fonctionVerifConfirmEmail()
{
	var email=document.getElementById("prodEmail");
	var emailConfirm=document.getElementById("prodConfirmEmail")
	var alerteEmailDifferentes=document.getElementById("alerteEmailDifferentes");

	if (email.value == emailConfirm.value)
	{

		alerteEmailDifferentes.setAttribute('style', 'visibility: hidden;');
		emailConfirm.style.borderBottom = "solid green 3px";
		verifBoutonEmail=true;
		verifBouton();
	}
	else
	{
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
		alerteEmailDifferentes.setAttribute('style', 'visibility: visible;');
		emailConfirm.style.borderBottom = "solid red 3px";

	}
}

function fonctionVerifNom()
{
	var nom=document.getElementById("prodNom");
	var alerteNom=document.getElementById("alerteNom");

	if (nom.value.length<2)
	{
		alerteNom.setAttribute('style', 'visibility:visible;');
		nom.style.borderBottom = "solid red 3px";
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
	}
	else
	{
		alerteNom.setAttribute('style', 'visibility:hidden;');
		nom.style.borderBottom = "solid green 3px";
		verifBoutonverifNom=true;
		verifBouton();
	}
}

function fonctionVerifPrenom()
{
	var prenom=document.getElementById("prodPrenom");
	var alertePreom=document.getElementById("alertePrenom");

	if (prenom.value.length<2)
	{
		alertePreom.setAttribute('style', 'visibility:visible;');
		prenom.style.borderBottom = "solid red 3px";
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
	}
	else
	{
		alertePreom.setAttribute('style', 'visibility:hidden;');
		prenom.style.borderBottom = "solid green 3px";
		verifBoutonverifPrenom=true;
		verifBouton();
	}
}

function fonctionVerifTelFix()
{
	var telFix=document.getElementById("prodTelFixe");
	var alerteTelFixe=document.getElementById("alerteTelFix");

	if (telFix.value.length<10)
	{
		alerteTelFixe.setAttribute('style', 'visibility:visible;');
		telFix.style.borderBottom = "solid red 3px";
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
	}
	else
	{
		alerteTelFixe.setAttribute('style', 'visibility:hidden;');
		telFix.style.borderBottom = "solid green 3px";
		verifBoutonTelFix=true;
		verifBouton();
	}
}

function fonctionVerifTelPortable()
{
	var telPortable=document.getElementById("prodTelPortable");
	var alerteTelPortable=document.getElementById("alerteTelPortable");

	if (telPortable.value.length<10)
	{
		alerteTelPortable.setAttribute('style', 'visibility:visible;');
		telPortable.style.borderBottom = "solid red 3px";
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
	}
	else
	{
		alerteTelPortable.setAttribute('style', 'visibility:hidden;');
		telPortable.style.borderBottom = "solid green 3px";
		verifBoutonTelPortable=true;
		verifBouton();
	}
}

function fonctionAutre()
{
	var autreText=document.getElementById("autreInputId");
	if (coche==false)
	{
		autreText.style.visibility = "visible";
		coche=true;
	}
	else
	{
		autreText.style.visibility = "hidden";
		coche=false;
	}

}

function fonctionMdp()
{
	var mdp=document.getElementById("prodMotDePasse");
	/*	var imgAjout=document.getElementById("imgMdp");*/
	var alertMdp=document.getElementById("alertMdp");
	var alertSpeciaux=document.getElementById("alertSpeciaux");
	var alertA=document.getElementById("alertA");
	var alertChar=document.getElementById("alertChar");
	var alertNum=document.getElementById("alertNum");



	var valeurMdp=mdp.value
	var valUpper = /[A-Z]/;
	var valLower = /[a-z]/;
	var valNum = /[0-9]/;

	var upper=false;
	var num=false;

	var puissanceMdp=0;

	for(var i=0 ; i < valeurMdp.length ; i++)
	{
		if (valUpper.test(valeurMdp[i]))
		{
			upper=true;
		}
		else
		{
			if (valNum.test(valeurMdp[i]))
			{
				num=true;
			}
		}
	}

	if (upper==true)
	{
		puissanceMdp++;
		alertA.style.color="#777777";
	}
	else
	{
		alertA.style.color="red";
	}

	if (num==true)
	{
		puissanceMdp++;
		alertNum.style.color="#777777";
	}
	else
	{
		alertNum.style.color="red";
	}

	if (mdp.value.indexOf("\@")!= -1 || mdp.value.indexOf("\.")!= -1 || mdp.value.indexOf("\/")!= -1 || mdp.value.indexOf("\!")!= -1 || mdp.value.indexOf("\?")!= -1 || mdp.value.indexOf("\,")!= -1 || mdp.value.indexOf("\;")!= -1 || mdp.value.indexOf("\:")!= -1 || mdp.value.indexOf("\ù")!= -1 || mdp.value.indexOf("\%")!= -1 || mdp.value.indexOf("\ù")!= -1 || mdp.value.indexOf("\*")!= -1 || mdp.value.indexOf("\^")!= -1 || mdp.value.indexOf("\$")!= -1 || mdp.value.indexOf("\£")!= -1 || mdp.value.indexOf("\¤")!= -1 || mdp.value.indexOf("\=")!= -1 || mdp.value.indexOf("\+")!= -1 || mdp.value.indexOf("\}")!= -1 || mdp.value.indexOf("\]")!= -1 || mdp.value.indexOf("\°")!= -1 || mdp.value.indexOf("\\")!= -1 || mdp.value.indexOf("\|")!= -1 || mdp.value.indexOf("\(")!= -1 || mdp.value.indexOf("\)")!= -1 || mdp.value.indexOf("\'")!= -1 || mdp.value.indexOf("\#")!= -1 || mdp.value.indexOf("\"")!= -1 || mdp.value.indexOf("\&")!= -1)
	{
		alertSpeciaux.style.color="#777777";
		puissanceMdp++;
	}
	else
	{
		alertSpeciaux.style.color="red";
	}

	if (mdp.value.length <3)
	{

		alertMdp.setAttribute('visibility','visible');
	}
	else
	{
		alertChar.style.color="red";
	}
	if (mdp.value.length <5 && mdp.value.length >2)
	{
		alertMdp.setAttribute('visibility','visible');
	}
	else
	{
		alertChar.style.color="red";
	}
	if (mdp.value.length <8 && mdp.value.length >4)
	{
		alertMdp.setAttribute('visibility','visible');
	}
	else
	{
		alertChar.style.color="red";
	}
	if (mdp.value.length >=10)
	{
		alertMdp.setAttribute('visibility','visible');
		alertChar.style.color="#777777";
		puissanceMdp++;


		verifPremier=true;
	}
	else
	{
		alertChar.style.color="red";
	}


	if (puissanceMdp==0)
	{
		/*imgAjout.setAttribute('src','mdpNul.jpg');*/
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
	}
	else
	if (puissanceMdp==1)
	{
		/*	imgAjout.setAttribute('src','mdpFaible.jpg');*/
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
	}
	if (puissanceMdp==2)
	{
		/*	imgAjout.setAttribute('src','mdpMoyen.jpg');*/
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
	}
	else
	if (puissanceMdp==3)
	{
		/*	imgAjout.setAttribute('src','mdpFort.jpg');*/
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');

	}
	else
	if (puissanceMdp==4)
	{
		/*	imgAjout.setAttribute('src','mdpBon.jpg');*/
		verifBoutonMdp=true;
		verifBouton();
	}

}

function fonctionConfirmMdp()
{
	var mdp=document.getElementById("prodMotDePasse");
	var confirmMdp=document.getElementById("prodConfirmMotDePasse");
	var alerteMdpDifferents=document.getElementById("alerteMdpDifferents");

	if (mdp.value == confirmMdp.value && mdp.value != "")
	{
		alerteMdpDifferents.setAttribute('style', 'visibility: hidden;');
		confirmMdp.style.borderBottom = "solid green 3px";
		verifBoutonConfirmMdp=true;
	}
	else
	{
		alerteMdpDifferents.setAttribute('style', 'visibility: visible;');
		confirmMdp.style.borderBottom = "solid red 3px";
		boutonEnvoyer.setAttribute('style', 'visibility: hidden;');
	}
	verifBouton();
}

function verifBouton()
{
	if (verifBoutonEmail==true && verifBoutonverifNom==true && verifBoutonverifPrenom==true && verifBoutonTelFix==true && verifBoutonTelPortable==true && verifBoutonMdp==true && verifBoutonConfirmMdp==true)
	{
		boutonEnvoyer.setAttribute('style', 'visibility: visible;');
	}
}


function fonctionAdresse()
{
	/*	var adresseProd=document.getElementById("prodAdressePostale");

	var lien="http://api-adresse.data.gouv.fr/search/?q=";

	var lienAdresse=adresseProd+lien;

	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
	if (this.readyState == 4 && this.status == 200)
	{
	reponse= JSON.parse(xhttp.responseText);
	nbResultats=jsonResponse.feature.length;
	var resultat=reponse.feature[0].properties.label;
	adresseProd.setAttribute('placeholder',resultat);
}
};
xhttp.open("GET", lienAdresse, true);
xhttp.send();*/
}
