// sidebar
document.addEventListener("DOMContentLoaded", function () {
    var menuButton = document.querySelector(".menu-btn");
    var sidebar = document.querySelector(".sidebar");
    let fa_count = 0;
    const fa = ["<i class=\"fa-solid fa-arrow-left\"></i>",
                /*"<i class=\"fa-solid fa-arrow-right\"></i>",*/
                "<i class=\"fa-solid fa-bars\"></i>"
                ];

    menuButton.addEventListener("click", function () {
      sidebar.classList.toggle("sidebar-visible");
      menuButton.classList.toggle("menu-btn-move");
      menuButton.innerHTML = fa[(fa_count)%2];
      fa_count++;
    });


    // History button
    var history_btn = document.getElementById("history-btn");
    history_btn.addEventListener("click", function(){
      window.alert("Still working");
    });
    // How to use button
    var setting_btn = document.getElementById("setting-btn");
    setting_btn.addEventListener("click", function(){
      menuButton.click();
      htu_btn.click();
    });
});


// overlay
function on() {
  document.querySelector(".overlay").style.display = "block";
}

function off() {
  document.querySelector(".overlay").style.display = "none";
}

document.addEventListener("DOMContentLoaded", function(){
  var overlay_mode= document.querySelector(".overlay");
  var menuButton = document.querySelector(".menu-btn");

  menuButton.addEventListener("click", function () {
    if(menuButton.innerHTML == "<i class=\"fa-solid fa-arrow-left\"></i>"){
      on();
    }
    else{
      off();
    }
  });

  overlay_mode.addEventListener("click", function(){
    off();
    menuButton.click();
  });
})


// overlay-2 (for 'How to use' button)
let htu_btn = document.getElementById("how-to-use-btn");
let overlay_2_mode = document.querySelector(".overlay-2");
htu_btn.addEventListener("click", function(){
  overlay_2_mode.style.display = "block";
  document.querySelector(".overlay-2-inside").style.display = "block";
})


overlay_2_mode.addEventListener("click", function(){
  overlay_2_mode.style.display = "none";
  document.querySelector(".overlay-2-inside").style.display = "none";
})