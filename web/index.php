<!DOCTYPE HTML>
<html>
    <head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>WaterMeter page</title>
	<table border="2" cellpadding="2" cellspacing="0" width = "430" align="center"  <frame bordercolor="black">
	    <caption><b>Teplota</b></caption> 
	    <tr style="color:white;background-color:darkblue;">
	    <th width="90" style="color:White;" >Datum </font> </th>
	    <th width="60">Cas</th>
	    <th width="60" nowrap >Aktualni spotreba</th>

		</tr> 
	    <?php
	    	$soubor  = fopen("./text.txt", "r");							 
	    	while (!feof($soubor)) 
			{
				echo"<tr>";
				$row = fgets($soubor);
				$items = explode("\t", $row);
	    		echo"<td align='center'>".$items[0]."</td>"; 
				echo"<td align='center'>".$items[1]."</td>";
                echo"<td align='center'>".$items[2]."</td>"; 				
	    		echo"</tr>";
	    	}
	    	// echo"<tr>";
	    	// echo "<td align = 'center'>Změřeno:</td>";
	    	// echo "<td colspan='5' align='center'>".fgets($soubor)."</td>";
	    	// echo"</tr>";
	    	fclose($soubor);
	    ?>	
	</table> 
    <img src="recognize.png" alt="Latest" align="right">	
    </head>
</html>