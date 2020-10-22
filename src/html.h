#ifndef HTML_H /* include guards */
#define HTML_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta charset="utf-8"/>
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    .water-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h1>GrowBoxBreeder V1.0</h1>

  <h2>Sensor 1 (DHT)</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature1">%TEMPERATURE1%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity1">%HUMIDITY1%</span>
    <sup class="units">&#37;</sup>
  </p>

  <h2>Sensor 2 (DHT)</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature2">%TEMPERATURE2%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity2">%HUMIDITY2%</span>
    <sup class="units">&#37;</sup>
  </p>

  <h2>Sensor 3 (DHT)</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature3">%TEMPERATURE3%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity3">%HUMIDITY3%</span>
    <sup class="units">&#37;</sup>
  </p>

  <h2>Wasserfüllstand</h2>
  <p>
    <i class="fas fa-water" style="color:#059e8a;"></i> 
    <span class="water-labels">Stand</span> 
    <span id="liquidlevel">%LIQUIDLEVEL%</span>
    <sup class="units">/4</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttpt1 = new XMLHttpRequest();
  xhttpt1.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature1").innerHTML = this.responseText;
    }
  };
  xhttpt1.open("GET", "/1/temperature", true);
  xhttpt1.send();

  var xhttph1 = new XMLHttpRequest();
  xhttph1.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity1").innerHTML = this.responseText;
    }
  };
  xhttph1.open("GET", "/1/humidity", true);
  xhttph1.send();

  var xhttpt2 = new XMLHttpRequest();
  xhttpt2.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature2").innerHTML = this.responseText;
    }
  };
  xhttpt2.open("GET", "/2/temperature", true);
  xhttpt2.send();

  var xhttph2 = new XMLHttpRequest();
  xhttph2.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity2").innerHTML = this.responseText;
    }
  };
  xhttph2.open("GET", "/2/humidity", true);
  xhttph2.send();

  var xhttpt3 = new XMLHttpRequest();
  xhttpt3.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature3").innerHTML = this.responseText;
    }
  };
  xhttpt3.open("GET", "/3/temperature", true);
  xhttpt3.send();

  var xhttph3 = new XMLHttpRequest();
  xhttph3.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity3").innerHTML = this.responseText;
    }
  };
  xhttph3.open("GET", "/3/humidity", true);
  xhttph3.send();

  var xhttphLevel = new XMLHttpRequest();
  xhttphLevel.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("liquidlevel").innerHTML = this.responseText;
    }
  };
  xhttphLevel.open("GET", "/liquidlevel", true);
  xhttphLevel.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

#endif /* HTML_H */