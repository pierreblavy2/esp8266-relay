#ifndef PAGE_HPP_
#define PAGE_HPP_

const String page(){

  return 
  R"xxxx(

  <!DOCTYPE html>
  <html lang="fr">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    
    <style>
	.collapsible {
	  background-color: #777;
	  color: white;
	  cursor: pointer;
	  padding: 18px;
	  width: 100%;
	  border: none;
	  text-align: left;
	  outline: none;
	  font-size: 15px;
	}

	.active, .collapsible:hover {
	  background-color: #555;
	}

	.content {
	  padding: 0 18px;
	  display: none;
	  overflow: hidden;
	  background-color: #f1f1f1;
	}
    </style>

       
  <title>VMC</title>
  </head>

  <body>

    <h1 class="collapsible", id="program">Programmation</h1>
    <div class="content">
    
    <p><b>Status</b><br></p>
    <table>
    <tr><td>Mode</td><td>$mode$</td></tr>
    <tr><td>VMC</td><td>$status_relay$</td></tr>
    <tr><td>Juste une fois</td><td>$status_once$</td></tr>
    </table>
    
    
    <form action="#" method="post">
    <p><b>Mode</b><br>
    <input type="radio" id="mode_on"   name="mode" value="mode_on"   $checked_mode_on$   > <label for="mode_on">Toujours ON</label><br>
    <input type="radio" id="mode_off"  name="mode" value="mode_off"  $checked_mode_off$  > <label for="mode_off">Toujours OFF</label><br>
    <input type="radio" id="mode_auto" name="mode" value="mode_auto" $checked_mode_auto$ > <label for="mode_auto">Programme</label><br>
    </p>
    
    <p><b>Programme matin</b><br>
    <input type="checkbox" id="h00" name="h00" title="De 00:00 à 00:59" $checked_h00$ ><label for="h00">00</label>
    <input type="checkbox" id="h01" name="h01" title="De 01:00 à 01:59" $checked_h01$ ><label for="h01">01</label>
    <input type="checkbox" id="h02" name="h02" title="De 02:00 à 02:59" $checked_h02$ ><label for="h02">02</label>
    <input type="checkbox" id="h03" name="h03" title="De 03:00 à 03:59" $checked_h03$ ><label for="h03">03</label>  
    <input type="checkbox" id="h04" name="h04" title="De 04:00 à 04:59" $checked_h04$ ><label for="h04">04</label>
    <input type="checkbox" id="h05" name="h05" title="De 05:00 à 05:59" $checked_h05$ ><label for="h05">05</label>
    <br>
    <input type="checkbox" id="h06" name="h06" title="De 06:00 à 06:59" $checked_h06$ ><label for="h00">06</label>
    <input type="checkbox" id="h07" name="h07" title="De 07:00 à 07:59" $checked_h07$ ><label for="h01">07</label>
    <input type="checkbox" id="h08" name="h08" title="De 08:00 à 08:59" $checked_h08$ ><label for="h02">08</label>
    <input type="checkbox" id="h09" name="h09" title="De 09:00 à 09:59" $checked_h09$ ><label for="h03">09</label>  
    <input type="checkbox" id="h10" name="h10" title="De 10:00 à 10:59" $checked_h10$ ><label for="h04">10</label>
    <input type="checkbox" id="h11" name="h11" title="De 11:00 à 11:59" $checked_h11$ ><label for="h05">11</label>
    <p><b>Programme après midi</b><br>
    <input type="checkbox" id="h12" name="h12" title="De 12:00 à 12:59" $checked_h12$ ><label for="h00">12</label>
    <input type="checkbox" id="h13" name="h13" title="De 13:00 à 13:59" $checked_h13$ ><label for="h01">13</label>
    <input type="checkbox" id="h14" name="h14" title="De 14:00 à 14:59" $checked_h14$ ><label for="h02">14</label>
    <input type="checkbox" id="h15" name="h15" title="De 15:00 à 15:59" $checked_h15$ ><label for="h03">15</label>  
    <input type="checkbox" id="h16" name="h16" title="De 16:00 à 16:59" $checked_h16$ ><label for="h04">16</label>
    <input type="checkbox" id="h17" name="h17" title="De 17:00 à 17:59" $checked_h17$ ><label for="h05">17</label>
    <br>
    <input type="checkbox" id="h18" name="h18" title="De 18:00 à 18:59" $checked_h18$ ><label for="h00">18</label>
    <input type="checkbox" id="h19" name="h19" title="De 19:00 à 19:59" $checked_h19$ ><label for="h01">19</label>
    <input type="checkbox" id="h20" name="h20" title="De 20:00 à 20:59" $checked_h20$ ><label for="h02">20</label>
    <input type="checkbox" id="h21" name="h21" title="De 21:00 à 21:59" $checked_h21$ ><label for="h03">21</label>  
    <input type="checkbox" id="h22" name="h22" title="De 22:00 à 22:59" $checked_h22$ ><label for="h04">22</label>
    <input type="checkbox" id="h23" name="h23" title="De 23:00 à 23:59" $checked_h23$ ><label for="h05">23</label>    
    </p>

    <p title="En mode programme, lance immédiatement la VMC pour la durée déterminée">
    <b>Programme juste une fois</b>
    <table>
    <tr>
    <td>
    <input type="radio" id="once_nochange"   name="once" value="once_nochange" checked>
    <label for="once_nochange">Ne rien changer</label>
    </td><td>
    <input type="radio" id="once_0"   name="once" value="once_0"  >
    <label for="once_0"></label>Annuler
    </td></tr>
    <tr><td>
    <input type="radio" id="once_15m" name="once" value="once_15m" >
    <label for="once_15m"> 15 minutes</label>
    </td><td>
    <input type="radio" id="once_1h"  name="once" value="once_1h"  >
    <label for="once_1h">  1 heure</label>
    </td></tr>
    <tr><td>
    <input type="radio" id="once_30m" name="once" value="once_30m" >
    <label for="once_30m"> 30 minutes</label>
    </td><td>
    <input type="radio" id="once_2h"  name="once" value="once_2h"  >
    <label for="once_2h">  2 heures</label>
    </td></tr>
    </table>

    <input type="submit" value="OK">
    </form>
    </div>
    
    <h1 class="collapsible">Wifi</h1>
    <div class="content">
    <p><b>Status</b><br>
    <table>
    <tr><td>Status</td><td>$wifi_mode$</td></tr>
    <tr><td>MAC</td><td>$wifi_mac$</td></tr>
     <tr><td>IP</td><td>$wifi_ip$</td></tr>
    <tr><td>SSID</td><td>$wifi_ssid$</td></tr>
    <tr><td>Stations connectées</td><td>$wifi_stationNum$</td></tr>
    <tr><td title="Tente de se connecter au wifi en mode station une fois le délais écoulé">AP timeout</td><td>$wifi_timeout$</td></tr>      
    </table>
    </p>
    
    <p><b>Connection</b><br>
    <form action="#" method="post">
    <table>
    <tr><td><label for="wifi_ssid">SSID</label></td><td><input type="text" id="wifi_ssid" name="wifi_ssid" value="$wifi_st_ssid$" /></td></tr>
    <tr><td><label for="wifi_pass">Pass</label></td><td><input type="text" id="wifi_pass" name="wifi_pass" value="" /></td></tr>
    </table>
    <br>
    <input type="submit" value="OK">
    </form>
    </p>
    </div>
    
    
    <h1 class="collapsible">Horloge</h1>
    <div class="content">
    <p><b>Status</b><br>
    <table>
    <tr><td>RTC statut</td>                    <td>$status_rtc$</td></tr>
    <tr><td>RTC température</td>               <td>$rtc_temperature$ °C</td></tr>
    <tr><td>Date et heure (UTC)</td>           <td>$utc_time$</td></tr>
    <tr><td>Date et heure (Europe/Paris)</td>  <td>$local_time$</td></tr>
    <tr><td>NTP mode actuel</td>               <td>$ntp_mode$</td></tr>
    <tr><td>NTP serveur</td>                   <td>$ntp_server$</td></tr>
    </table>
    </p>
    
    <p><b>Configuration</b><br>
    <form action="#" method="post">
    <input type="radio" id="ntp_nochange"   name="ntp_mode" value="ntp_nochange"   checked >
    <label for="ntp_nochange">Ne rien changer</label><br>

    <input type="radio" id="ntp_on"   name="ntp_mode" value="ntp_on">
    <label for="mode_on">NTP</label>
    <input type="text" id="ntp_server" name="ntp_server" value="$ntp_server$"  title="Serveur ntp. Example europe.pool.ntp.org"/><br>
    <br>
        
    <input type="radio" id="ntp_off"  name="ntp_mode" value="ntp_off"> 
    <label for="mode_off">Manuel</label>
    <input type="date" id="date" name="date" value="$current_date$">
    <input type="time" id="time" name="time" value="$current_time$"><br>
    <input type="submit" value="OK">
    </form>
    </p>
    </div>
    
    
    
    
    
  <script>
	var coll = document.getElementsByClassName("collapsible");
	var i;

	for (i = 0; i < coll.length; i++) {
	  coll[i].addEventListener("click", function() {
	    this.classList.toggle("active");
	    var content = this.nextElementSibling;
	    if (content.style.display === "block") {
	      content.style.display = "none";
	    } else {
	      content.style.display = "block";
	    }
	  });
	}
	
	
  document.getElementById("program").click();
  </script>
 

  </body>
</html>

)xxxx";
}

#endif
