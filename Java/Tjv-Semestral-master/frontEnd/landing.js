class order{
  constructor(products, deliverTo, siteUserId){
    this.productIds = products;
    this.deliverTo = deliverTo;
    this.siteUserId = siteUserId;
  }
}


window.onload = function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        // Parse the JSON response
        var response = JSON.parse(this.responseText);

        // Convert the response to a string and format it
      var responseString = "";
      for (var i = 0; i < response.length; i++) {
        responseString += JSON.stringify(response[i], null, 2) + "\n\n";
      }
        // Display the response as plaintext on the page
        document.getElementById("result").value = responseString;
      }
    };
    xhttp.open("GET", "http://localhost:6060/product", true);
    xhttp.send();
  }

function orderProducts(event){
  event.preventDefault();
  var toSend = new order();
  toSend.productIds = parseArray( document.getElementById("productIds").value );
  toSend.deliverTo = document.getElementById("deliverTo").value;
  toSend.siteUserId = + document.getElementById("siteUserId").value;

  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      alert("Order created!");
    }
    else if(this.readyState == 4){
      alert("something is wrong! Server returned: " + this.status);
    }
  };
  console.log(JSON.stringify(toSend));
  xhttp.open("POST", "http://localhost:6060/order", true);
  xhttp.setRequestHeader("Content-Type", "application/json");
  xhttp.send(JSON.stringify(toSend));
}

function parseArray(json) {
  return JSON.parse(json, (key, value) => {
    if (typeof value === "string" && value.startsWith("[") && value.endsWith("]")) {
      return value
        .substring(1, value.length - 1)
        .split(",")
        .map(Number);
    }
    return value;
  });
}