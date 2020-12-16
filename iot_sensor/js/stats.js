$(document).ready(function(){
  $.ajax({
    url : "value_data.json",
    type : "GET",
    success : function(data){
      //console.log(data);

      var time = [];
      var lg_sound = [];

      for(var i in data) {
        time.push(data[i].timestamp);
        lg_sound.push(data[i].lung_sound);
      }

  //get the line chart canvas
  //var ctx = document.getElementById("line-chartcanvas").getContext('2d');

  //line chart data
  var data = {
    labels: time,
    datasets: [
      {
        label: "Lung Sound",
        data: lg_sound,
        backgroundColor: "blue",
        borderColor: "lightblue",
        fill: false,
        lineTension: 0,
        radius: 5
      }
    ]
  };

  //options
  var options = {
    responsive: true,
    title: {
      display: true,
      position: "top",
      text: "Lung Sound",
      fontSize: 18,
      fontColor: "#111"
    },
    legend: {
      display: true,
      position: "bottom",
      labels: {
        fontColor: "#333",
        fontSize: 16
      }
    }
  };

  //create Chart class object
  var ctx = $("#line-chartcanvas");
  var chart = new Chart(ctx, {
    type: "line",
    data: data,
    options: options
  });
  },
  error : function(data) {
	document.write('<h1>There was an error loading the page.</h1>');
  }
  });
});
