<?php
//verifico che provenga da arduino: password
	if($_POST["password"]=="serrarduino1994"){
		//leggo ip 
			$ip_p=$_SERVER['REMOTE_ADDR'];
			$ip_l=$_POST["local_ip"];
		//salvo ip nel database
			include("connessione.php");
			
			$sql="UPDATE ip_address SET ip_date=NOW(), ip_public='".$ip_p."', ip_local='".$ip_l."';";
			$ris=mysql_query($sql) or die ("Errore Query");

			mysql_close();
			
			echo $ip_p;
			echo $ip_l;
	}
	else echo "Richiesta non autorizzata.";


?>
 