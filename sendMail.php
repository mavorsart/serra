<?php
//verifico che provenga da arduino: password
	if($_POST['password']=="serrarduino1994"){
		
		$email="serrarduino@altervista.org";
		$destinatario="marcosartini.ms@gmail.com";
		
					
		$mittente="From: ".$email."\r\n";		
		$oggetto= $_POST['codice']." - SerrArduino";
		$messaggio="Buongiorno,\nla tua serra ti lascia questo messaggio: ".$_POST['errore']."\nControlla il suo stato.\nSerrArduino";
		
		mail($destinatario,$oggetto,$messaggio,$mittente);
		echo "E-mail inviata con successo.";
	}
		else {
		echo "Richiesta non autorizzata.";
		}
						
	?>