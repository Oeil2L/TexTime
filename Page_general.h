//
//  HTML PAGE
//

const char PAGE_general[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>General Settings</strong>
<hr>
<form action="" method="post">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Brightness auto :</td><td><input type="checkbox" id="brightnessauto" name="brightnessauto" value="" onclick="updatebrightnessauto()"></td></tr>
<tr><td align="right">Brightness manual :</td><td><input type="range" id="brightness" name="brightness" max="255" min="0" step="1" onchange="updatebrightness()"><span id="brightnesst" name="brightnesst">--</span></td></tr>
<tr><td align="right">Min day brightness :</td><td><input type="range" id="brightnessday" name="brightnessday" max="255" min="0" step="1" onchange="updatebrightnessday()"><span id="brightnessdayt" name="brightnessdayt">--</span></td></tr>
<tr><td align="right">Min night brightness :</td><td><input type="range" id="brightnessnight" name="brightnessnight" max="255" min="0" step="1" onchange="updatebrightnessnight()"><span id="brightnessnightt" name="brightnessnightt">--</span></td></tr>
<tr><td align="right">Color :</td><td><input class="jscolor" onchange="updatecolor(this.jscolor)" value="" id="color" name="color" ></td></tr>
<tr><td align="right">Color Random :</td><td>
<select  id="colorrandom" name="colorrandom" onchange="updatecolorrandom()" >
  <option value="0">No Random</option>
  <option value="1">Random all</option>
  <option value="2">Random letter</option>
  <option value="3">Random word</option>
</select>
</td></tr>
<tr><td align="right">Mode :</td><td>
<select  id="mode" name="mode" onchange="updatemode()" >
  <option value="1">Nothing</option>
  <option value="2">Time</option>
  <option value="3">Second</option>
  <option value="4">Day</option>
  <option value="5">Temperature</option>
</select>
</td></tr>
<tr><td align="right">Animation :</td><td>
<select  id="animation" name="animation" onchange="updateanimation()" >
  <option value="0">Normal</option>
  <option value="1">Blink</option>
  <option value="2">Fire</option>
  <option value="3">Matrix</option>
  <option value="4">Pong Auto</option>
  <option value="5">Pong Manual</option>
  <option value="6">Alphabet</option>
  <option value="7">Rainbow w/ bg</option>
  <option value="8">Rainbow w/o bg</option>
</select>
</td></tr>

<tr><td colspan="2" align="center"><a href="javascript:LedMode(100); void 0" class="btn btn--m btn--blue">Test Leds</a></td></tr>

<tr><td colspan="2" align="center"><hr></td></tr>

<tr><td colspan="2" align="center"><a href="javascript:LedPong(-1); void 0" class="btn btn--m btn--blue" id="ledpongA" style="visibility:hidden">&lt;&lt;&lt;</a> <a href="javascript:LedPong(1); void 0" class="btn btn--m btn--blue" id="ledpongB" style="visibility:hidden">&gt;&gt;&gt;</a></td></tr>

<tr><td colspan="2" align="center"><hr></td></tr>

<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
</table>
</form>
<script>

function displayPlayPong() {
  if (document.getElementById("animation").value == 5)
  {
    document.getElementById("ledpongA").style.visibility = "visible";
    document.getElementById("ledpongB").style.visibility = "visible";
  }
  else
  {
    document.getElementById("ledpongA").style.visibility = "hidden";
    document.getElementById("ledpongB").style.visibility = "hidden";
  }
}

function LedPong(p) {
  setValues("/admin/led?pong=" + p);
}

function updatebrightness() {
  document.getElementById("brightnesst").innerHTML = document.getElementById("brightness").value;
  setValues("/admin/led?brightness=" + document.getElementById("brightness").value);
}

function updatebrightnessday() {
  document.getElementById("brightnessdayt").innerHTML = document.getElementById("brightnessday").value;
  setValues("/admin/led?brightnessday=" + document.getElementById("brightnessday").value);
}

function updatebrightnessnight() {
  document.getElementById("brightnessnightt").innerHTML = document.getElementById("brightnessnight").value;
  setValues("/admin/led?brightnessnight=" + document.getElementById("brightnessnight").value);
}

function updatecolor(picker) {
  setValues("/admin/led?color=" + picker);
}

function updatecolorrandom() {
  setValues("/admin/led?colorrandom=" + document.getElementById("colorrandom").value);
}

function updatemode() {
  LedMode(document.getElementById("mode").value);
}

function updateanimation() {
  setValues("/admin/led?animation=" + document.getElementById("animation").value);

  displayPlayPong();
}

function validatebrightnessauto() {
  document.getElementById("brightness").disabled = document.getElementById('brightnessauto').checked;
  document.getElementById("brightnessday").disabled = !document.getElementById('brightnessauto').checked;
  document.getElementById("brightnessnight").disabled = !document.getElementById('brightnessauto').checked;

  document.getElementById("brightnesst").innerHTML = document.getElementById("brightness").value;
  document.getElementById("brightnessdayt").innerHTML = document.getElementById("brightnessday").value;
  document.getElementById("brightnessnightt").innerHTML = document.getElementById("brightnessnight").value;
}

function updatebrightnessauto() {
  validatebrightnessauto();
  if (document.getElementById('brightnessauto').checked)
    setValues("/admin/led?brightness=-1");
}

function LedMode(v)
{
  setValues("/admin/led?mode=" + v);
}

window.onload = function ()
{
	load("style.css","css", function() 
	{
		load("microajax.js","js", function() 
		{
				setValues("/admin/generalvalues");
        setTimeout(validatebrightnessauto,1000);
		});
	});
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}



</script>
)=====";



void send_general_html()
{
	
	if (_server.args() > 0 )  // Save Settings
	{
    _config.brightnessAuto = false;
		for ( uint8_t i = 0; i < _server.args(); i++ ) {
      if (_server.argName(i) == "brightnessauto") _config.brightnessAuto = true;
      if (_server.argName(i) == "brightness") _config.brightness = _server.arg(i).toInt();
      if (_server.argName(i) == "brightnessday") _config.brightnessAutoMinDay = _server.arg(i).toInt();
      if (_server.argName(i) == "brightnessnight") _config.brightnessAutoMinNight = _server.arg(i).toInt();
      if (_server.argName(i) == "color")
      {
        int32_t l = strtol(_server.arg(i).c_str(), 0, HEX);
        _config.color[0] = (l >> 16) & 0xFF;
        _config.color[1] = (l >> 8) & 0xFF;
        _config.color[2] = (l >> 0) & 0xFF;
      }
      if (_server.argName(i) == "mode") _config.mode = _server.arg(i).toInt();
      if (_server.argName(i) == "animation") _config.animation = _server.arg(i).toInt();
      if (_server.argName(i) == "colorrandom") _config.colorRandom = _server.arg(i).toInt();
    }

		WriteConfig();

    QTLed.setAutomaticBrightness(_config.brightnessAuto);
    if (!_config.brightnessAuto)
      QTLed.setBrightness(_config.brightness);

    QTLed.setColor(_config.color[0], _config.color[1], _config.color[2]);
    QTLed.setColorRandom((MyLedStripColorRandom)_config.colorRandom);

    QTLed.setMode((MyLedStripMode)_config.mode);
    QTLed.setAnimMode((MyLedStripAnimatorMode)_config.animation);

    //ESP.restart();
	}
  _server.send_P(200, "text/html", PAGE_general);
	//Serial.println(__FUNCTION__); 	
}


void send_general_configuration_values_html()
{
	String values ="";
  values += "brightnessauto|" + (String)(_config.brightnessAuto ? "checked" : "") + "|chk\n";
  values += "brightness|" + (String)_config.brightness + "|input\n";
  values += "brightnessday|" + (String)_config.brightnessAutoMinDay + "|input\n";
  values += "brightnessnight|" + (String)_config.brightnessAutoMinNight + "|input\n";
  values += "color|" + dec2hex2(_config.color[0]) + dec2hex2(_config.color[1]) + dec2hex2(_config.color[2]) + "|jscolor\n";
  values += "mode|" + (String)_config.mode + "|input\n";
  values += "animation|" + (String)_config.animation + "|input\n";
  values += "colorrandom|" + (String)_config.colorRandom + "|input\n";

	_server.send(200, "text/plain", values);
	//Serial.println(__FUNCTION__); 
}

void send_general_led()
{
  if (_server.args() > 0)
  {
    for (uint8_t i = 0; i < _server.args(); i++) {
      if (_server.argName(i) == "brightness")
      {
        int b = _server.arg(i).toInt();
        if (b < 0)
          QTLed.setAutomaticBrightness(true);
        else
        {
          QTLed.setAutomaticBrightness(false);
          QTLed.setBrightness(_server.arg(i).toInt());
        }
      }

      if (_server.argName(i) == "brightnessday")
        _config.brightnessAutoMinDay = _server.arg(i).toInt();

      if (_server.argName(i) == "brightnessnight")
        _config.brightnessAutoMinNight = _server.arg(i).toInt();


      if (_server.argName(i) == "mode")
      {
        QTLed.setMode((MyLedStripMode)_server.arg(i).toInt());
      }

      if (_server.argName(i) == "color")
      {
        int32_t l = strtol(_server.arg(i).c_str(), 0, HEX);
        byte r = (l >> 16) & 0xFF;
        byte g = (l >> 8) & 0xFF;
        byte b = (l >> 0) & 0xFF;

        QTLed.setColor(r, g, b);
      }

      if (_server.argName(i) == "animation")
      {
        QTLed.setAnimMode((MyLedStripAnimatorMode)_server.arg(i).toInt());
      }

      if (_server.argName(i) == "colorrandom")
      {
        QTLed.setColorRandom((MyLedStripColorRandom)_server.arg(i).toInt());
      }

      if (_server.argName(i) == "pong")
      {
        QTLed.setPongModePlay1posManual(_server.arg(i).toInt());
      }
    }
  }
  _server.send(200, "text/plain", "OK");
}