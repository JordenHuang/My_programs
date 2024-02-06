//------------------- PART 0 - menu button part and others--------------------------//
// device type
const isMobile = /android|webos|iphone|ipad|ipod|blackberry|iemobile|opera mini/i.test(navigator.userAgent.toLowerCase());


// for menu button
let menu_btn = document.querySelector(".menu-btn");
let overlay_mode = document.querySelector(".overlay");

menu_btn.addEventListener("click", function(){
  overlay_mode.style.display = "block";
  document.querySelector(".overlay-inside").style.display = "block";
})

overlay_mode.addEventListener("click", function(){
  overlay_mode.style.display = "none";
  document.querySelector(".overlay-inside").style.display = "none";
})



// button inside overlay ( = menu) 
let restart = document.getElementById("restart");
let home = document.getElementById("home");
let hide_time = document.getElementById("hide-time");

function to_restart(){
    let conf = confirm("Are you sure you want to RESTART?");
    if(conf == true){
        window.location.pathname = "/card_memo_trainer/start_page.html";
    }
}

function go_home(){
    let conf = confirm("Are you sure you want to QUIT?");
    if(conf == true){
        window.location.pathname = "/card_memo_trainer/index.html";
    }
}

function to_hide_or_show_time(){
    let time_num_display = document.querySelector(".timer");
    let time_num_not_display = document.querySelector(".timer-not-show");

    let countdown_time_num_display = document.querySelector(".count-down-timer");
    let countdown_time_num_not_display = document.querySelector(".count-down-timer-not-show");

    
    if(hide_time.textContent === "Hide time"){
        hide_time.textContent = "Show time";
        time_num_display.style.display = "none";
        time_num_not_display.style.display = "block";

        countdown_time_num_display.style.display = "none";
        countdown_time_num_not_display.style.display = "block";
    }
    else if(hide_time.textContent === "Show time"){
        hide_time.textContent = "Hide time";
        time_num_display.style.display = "block";
        time_num_not_display.style.display = "none";

        countdown_time_num_display.style.display = "block";
        countdown_time_num_not_display.style.display = "none";
    }
}

restart.addEventListener("click", to_restart);
home.addEventListener("click", go_home);
hide_time.addEventListener("click", to_hide_or_show_time);


let loading = document.getElementById("loading");
// loading.style.display = "none";




//------------------- PART I - memorization page ----------------------------------//

// part 2 的開關
let part_1_done = false;

// buttom overlay-bar
// (click it to change the image)
const images = ["card_pics/ace_of_clubs.png",
    "card_pics/ace_of_diamonds.png",
    "card_pics/ace_of_hearts.png",
    "card_pics/ace_of_spades2.png",
    "card_pics/2_of_clubs.png",
    "card_pics/2_of_diamonds.png",
    "card_pics/2_of_hearts.png",
    "card_pics/2_of_spades.png",
    "card_pics/3_of_clubs.png",
    "card_pics/3_of_diamonds.png",
    "card_pics/3_of_hearts.png",
    "card_pics/3_of_spades.png",
    "card_pics/4_of_clubs.png",
    "card_pics/4_of_diamonds.png",
    "card_pics/4_of_hearts.png",
    "card_pics/4_of_spades.png",
    "card_pics/5_of_clubs.png",
    "card_pics/5_of_diamonds.png",
    "card_pics/5_of_hearts.png",
    "card_pics/5_of_spades.png",
    "card_pics/6_of_clubs.png",
    "card_pics/6_of_diamonds.png",
    "card_pics/6_of_hearts.png",
    "card_pics/6_of_spades.png",
    "card_pics/7_of_clubs.png",
    "card_pics/7_of_diamonds.png",
    "card_pics/7_of_hearts.png",
    "card_pics/7_of_spades.png",
    "card_pics/8_of_clubs.png",
    "card_pics/8_of_diamonds.png",
    "card_pics/8_of_hearts.png",
    "card_pics/8_of_spades.png",
    "card_pics/9_of_clubs.png",
    "card_pics/9_of_diamonds.png",
    "card_pics/9_of_hearts.png",
    "card_pics/9_of_spades.png",
    "card_pics/10_of_clubs.png",
    "card_pics/10_of_diamonds.png",
    "card_pics/10_of_hearts.png",
    "card_pics/10_of_spades.png",
    "card_pics/jack_of_clubs2.png",
    "card_pics/jack_of_diamonds2.png",
    "card_pics/jack_of_hearts2.png",
    "card_pics/jack_of_spades2.png",
    "card_pics/queen_of_clubs2.png",
    "card_pics/queen_of_diamonds2.png",
    "card_pics/queen_of_hearts2.png",
    "card_pics/queen_of_spades2.png",
    "card_pics/king_of_clubs2.png",
    "card_pics/king_of_diamonds2.png",
    "card_pics/king_of_hearts2.png",
    "card_pics/king_of_spades2.png",
    // "card_pics/poker-card-back.png",
    // "card_pics/poker-card-back.png",
    // "card_pics/poker-card-back.png"
];
const cards = 54;


let shuffled_img = Array.from(images);
let bar = document.querySelector(".bar");
let box1 = document.querySelector(".box1 img");
let box2 = document.querySelector(".box2 img");
let box3 = document.querySelector(".box3 img");
let memoed = document.querySelector(".memoed img");
let next_card = document.querySelector(".next img");
let card_count = 0;



function shuffle(array){
    let current_index = array.length;
    let random_shuffle_count = Math.floor(Math.random() * (11-5) +5);
    console.log("shuffle count:",random_shuffle_count)
    for(let i=0; i<random_shuffle_count; i+=1){
        while(current_index != 0){
            let random_index = Math.floor(Math.random() * array.length);
            if(random_index === current_index) continue;
            current_index -= 1;

            let temp = array[current_index];
            array[current_index] = array[random_index];
            array[random_index] = temp;
        }
        // reset current_index
        current_index = array.length;
    }

    // add three card-backs to the end of the array
    for(let i=0; i<3; i+=1){
        array.push("card_pics/poker-card-back.png");
    }

    return array;
}

function preload_img(img_arr){
    for(i=0; i<52; i++){
        let img = new Image();
        img.src = img_arr[i];
    }
    loading.style.display = "none";
}

function change_img(l_or_r){
    switch(l_or_r.bar){
        case 0: default:
            if(card_count === 0){
                bar.textContent = "click here to change to next card";
                box3.src = shuffled_img[card_count++];
                box2.src = shuffled_img[card_count++];
                box1.src = shuffled_img[card_count++];
                // after this if statement, card_count is 3 now
                next_card.src = shuffled_img[card_count];
                memoed.src = shuffled_img[shuffled_img.length-1];
            }
            else if((card_count-2) < 52){ // 因為第一下是翻開，到最後是兩張牌背時，就停止
                memoed.src = box3.src;
                box3.src = box2.src;
                box2.src = box1.src;
                box1.src = shuffled_img[card_count++];
                next_card.src = shuffled_img[card_count];

                // if(card_count === 54){
                //     card_count = 0;
                // }
            }
            break;
        
        case 2:
            //TODO: right click to go back to the last card

    }
}

shuffle(shuffled_img);
preload_img(shuffled_img);
bar.addEventListener("click", change_img);





// count-up timer
let time_display = document.querySelector(".timer");
let mins = 0;
let secs = 0;
let msecs = 0;

let elapse_time = 0;
let start_time = 0;
let interval_id;

let once = true;
let time_used = "";

let card_container_display = document.querySelector(".card-container");


// Update time in stopwatch periodically - every 25ms
function pad(unit){
    return ('0' + unit).length > 2 ? unit : '0' + unit;
}

function update_timer(){     
    start_time = Date.now();   
    interval_id = setInterval(function () {
        // calculate the time elapsed in milliseconds
        elapse_time = Date.now() - start_time;

        msecs = Math.floor(elapse_time % 1000 /10);
        // console.log(Math.floor(elapse_time/1000) ,':', elapse_time%1000);
        secs = Math.floor(elapse_time/1000 % 60);
        mins = Math.floor(elapse_time/(1000*60) % 60);

        msecs = pad(msecs);
        secs = pad(secs);
        mins = pad(mins);

        time_display.textContent = `${mins}:${secs}:${msecs}`;
        
    }, 25); // update time in stopwatch after every 25ms
}

// most important part of the first part (memorization page)
bar.addEventListener("click", function(){
    if(once){
        once = false;
        update_timer();
    }
    if(card_count === cards){
        time_used = `${parseInt(mins)}<sub>min</sub> ${parseInt(secs)}<sub>sec</sub> ${parseInt(msecs)}<sub>ms</sub>`;
        clearInterval(interval_id);
        console.log(`clear part 1, total time is ${mins}:${secs}:${msecs}`);
        setTimeout(() => {
            // console.log("Delayed for 1.2 second");

            // disable the button of time visibility 
            if(hide_time.textContent === "Show time"){
                hide_time.click();
            }

            // not showing previous screen
            card_container_display.style.display = "none";

            // let elems = document.getElementsByClassName('checker-container');
            // for (let i=0;i<elems.length;i+=1){
            //     elems[i].style.display = 'block';
            // }
            

            // 開啟 part 2 的開關
            part_1_done = true;

            loading.style.display = "block";
            
        }, 1200);

        // remove event listener
        bar.removeEventListener("click", change_img);
        bar.removeEventListener("click", arguments.callee);
        console.log('bar.close');
    }
})


// use keyboard to go to show next card
window.addEventListener("keydown", function(e){
    var key_id = e.code;
    // console.log(key_id);
    

    switch(key_id){
    case "KeyZ":
    case "ArrowRight":
        bar.click();
        break;
    
    case "KeyX":
    case "ArrowUp":
        bar.click();
        bar.click();
        bar.click();
        break;
    default:
        // console.log(key_id);
        break;
    }
})





//------------------- PART II - check page ----------------------------------//

// part 3 的開關
let part_2_done = false;



// the three lines below are not working
    // let checker_container = document.querySelector(".checker-container");
    // checker_container.sytle.display = "none";
    // console.log(checker_container);

// but the codes below are working (from stack overflow)
// let elems = document.getElementsByClassName('checker-container');
// for (let i=0;i<elems.length;i+=1){
//     elems[i].style.display = 'block';
// }





// card selections
let pic = document.getElementsByClassName("checker-selection-box");
let spades_btn = document.getElementById("spades");
let hearts_btn = document.getElementById("hearts");
let diamonds_btn = document.getElementById("diamonds");
let clubs_btn = document.getElementById("clubs");

let spades = ["_spades"];
let hearts = ["_hearts"];
let diamonds = ["_diamonds"];
let clubs = ["_clubs"];

let last_click_sute_btn = "";

// assign cards to those suits
for(let i=0; i<52; i+=1){
    let index = i % 4;
    switch(index){
        case 3:
            spades.push(images[i]);
            // console.log(images[i]);
            break;

        case 2:
            hearts.push(images[i]);
            break;

        case 1:
            diamonds.push(images[i]);
            break;

        case 0:
            clubs.push(images[i]);
            break;

        // default:
        //     console.log("nonono", i)
    }
}

function change_suits(array){
    array.forEach(function(value, index){
        if(index === 0) last_click_sute_btn = value;
        else if(value.slice(0, 2) === "h_"){
            pic[index-1].style.visibility = "hidden";
        }
        else{
            pic[index-1].style.visibility = "visible";
            // -1 due to the first element is the array name
            pic[index-1].src = value;
            pic[index-1].id = array[0];
        }
    })
}

// initialization - show spades' cards
change_suits(spades);

spades_btn.addEventListener("click", () => change_suits(spades));
hearts_btn.addEventListener("click", () => change_suits(hearts));
diamonds_btn.addEventListener("click", () => change_suits(diamonds));
clubs_btn.addEventListener("click", () => change_suits(clubs));



// selection parts

// 52 checkers
let checker_group = document.querySelector(".checker-group");
let checker_to_fill = checker_group.children[0];
// console.log(checker_group.children[0]);

let highlight = "margin: 2px; border: 2.5px red solid; border-radius: 5px;";
let original_style = "margin: 4.5px; border-style: solid; border-radious: 0px;"

checker_to_fill.style.cssText = highlight;

// 13 selections
let selections = document.querySelector(".checker-selection-group");

let selected_card = " ";

function next_checker_to_fill(checker_to_fill){
    if(checker_to_fill.nextElementSibling != undefined){
        checker_to_fill = checker_to_fill.nextElementSibling;
    }
    // else{
    //     if(checker_to_fill.parentElement.nextElementSibling.className === "checker-group"){
    //         checker_to_fill = checker_to_fill.parentElement.nextElementSibling.children[0];
    //     }
    //     else return checker_group.children[0].children[0];
    // }
    return checker_to_fill;
}


function checker_choosing(array, string, checker_to_fill, selected_card){
    var reload = false;

    if(checker_to_fill.src != ''){
        reload = true;

        let last_array = [];

        switch(checker_to_fill.id){
            case "_spades":
                last_array = spades;
                break;
            case "_hearts":
                last_array = hearts;
                break;
            case "_diamonds":
                last_array = diamonds;
                break;
            case "_clubs":
                last_array = clubs;
                break;
        }

        // remove the 'h_' prefix of the array element
        let index = last_array.indexOf("h_"+checker_to_fill.src.slice(checker_to_fill.src.indexOf("card_pics")));
        // console.log(index);

        if(index != -1) last_array[index] = last_array[index].slice(2);

        // index == -1 only when double click
        // else if(index === -1) last_array[index] = last_array[index];
    }

    // 牌會從selections消失並顯示在checker-box的重點
    selected_card = array[array.indexOf(string)];
    checker_to_fill.src = selected_card;
    array[array.indexOf(string)] = "h_" + selected_card;

    if(reload) change_suits(array);

    return [array, checker_to_fill, selected_card];
}


function click_selections(e){
    // console.log(e);
    // console.log(e.target);
    // console.log(e.target.tagName);
    // console.log(e.target.alt);
    // console.log(e.target.id);
    let target_src = e.target.src;
    let target_tag_name = e.target.tagName;

    if(target_tag_name === "IMG"){
        e.target.style.visibility = 'hidden';
        let string = target_src.slice(target_src.indexOf("card_pics"));
        let data = [];

        switch(e.target.id.slice(1)){
            case "spades":             
                data = checker_choosing(spades, string, checker_to_fill, selected_card);
                spades = data[0];
                checker_to_fill = data[1];
                checker_to_fill.id = "_spades";
                selected_card = data[2];
                break;
            case "hearts":
                data = checker_choosing(hearts, string, checker_to_fill, selected_card);
                hearts = data[0];
                checker_to_fill = data[1];
                checker_to_fill.id = "_hearts";
                selected_card = data[2];
                break;
            case "diamonds":
                data = checker_choosing(diamonds, string, checker_to_fill, selected_card);
                diamonds = data[0];
                checker_to_fill = data[1];
                checker_to_fill.id = "_diamonds";
                selected_card = data[2];
                break;
            case "clubs":
                // selected_card = clubs[clubs.indexOf(string)]
                // checker_to_fill.src = selected_card;
                // clubs[clubs.indexOf(string)] = "h_" + selected_card;
                data = checker_choosing(clubs, string, checker_to_fill, selected_card);
                clubs = data[0];
                checker_to_fill = data[1];
                checker_to_fill.id = "_clubs";
                selected_card = data[2];
                break;
            case 'h':
                break;
        }

        checker_to_fill.style.cssText = original_style;

        checker_to_fill = next_checker_to_fill(checker_to_fill);

        checker_to_fill.style.cssText = highlight;
    }
}

function click_checker(group){
    // console.log(group);
    let target_class_name = group.target.className;
    // console.log(group.target);

    if(target_class_name === "checker-box"){
        // console.log(spades);
        // console.log(checker_to_fill.src);
        // console.log(checker_to_fill);

        if(checker_to_fill != ' '){
            checker_to_fill.style.cssText = original_style;
        }

        checker_to_fill = group.target;
        checker_to_fill.style.cssText = highlight;
    }
}

function dbclick_checker(group){
    let target_class_name = group.target.className;

    if(target_class_name === "checker-box"){
        if(checker_to_fill.src != ' '){
            let last_array = [];
            switch(checker_to_fill.id){
                case "_spades":
                    last_array = spades;
                    break;
                case "_hearts":
                    last_array = hearts;
                    break;
                case "_diamonds":
                    last_array = diamonds;
                    break;
                case "_clubs":
                    last_array = clubs;
                    break;
            }
            // remove the 'h_' prefix of the array element
            let index = last_array.indexOf("h_"+checker_to_fill.src.slice(checker_to_fill.src.indexOf("card_pics")));
            // -1 due to double click
            if(index != -1) last_array[index] = last_array[index].slice(2);

            checker_to_fill.src = ' ';


            // for not changing the suit of current selections
            if(checker_to_fill.id === last_click_sute_btn){
                change_suits(last_array);
            }           
        }
    }
}


selections.addEventListener("click", click_selections);

checker_group.addEventListener("click", click_checker);

if(isMobile == false) {
    checker_group.addEventListener("dblclick", dbclick_checker);
}
else {
    checker_group.addEventListener("touchmove", dbclick_checker);
}



// finish-btn
let finish_btn = document.getElementById("finish-btn");

function click_finish_btn(){
    // TODO: if not all fill in, add confirm
    let all = false;

    clearTimeout(countdown_timerId);
    count_down_timer.textContent = "00:00";


    // remove some button event listeners
    selections.removeEventListener("click", click_selections);

    checker_group.removeEventListener("click", click_checker);

    if(isMobile == false) {
        checker_group.removeEventListener("dblclick", dbclick_checker);
    }
    else {
        checker_group.removeEventListener("touchmove", dbclick_checker);
    }


    // remove Hide time/Show time button
    hide_time.removeEventListener("click", to_hide_or_show_time);
    hide_time.remove();


    finish_btn.removeEventListener("click", click_finish_btn);
    
    let elems = document.getElementsByClassName('checker-container');
    for (let i=0;i<elems.length;i+=1){
        elems[i].style.display = 'none';
    }

    loading.style.display = "block";

    // 開啟 part 3 的開關
    part_2_done = true;
}

finish_btn.addEventListener("click", click_finish_btn);



// count-down timer - for 5 minutes

let timeLeft = 60 * 5;  // 其實應該要-1，但因為這樣看起來太急，所以算了
let count_down_timer = document.querySelector(".count-down-timer");

let countdown_min = 0;
let countdown_sec = 0;

let countdown_timerId;

function countdown() {
    if (timeLeft === 0) {
        finish_btn.click();
    }
    else{
        timeLeft--;
        countdown_min = pad(Math.floor(timeLeft / 60));
        countdown_sec = pad(timeLeft % 60);
        count_down_timer.textContent = `${countdown_min}:${countdown_sec}`;

        if(timeLeft === 0) count_down_timer.textContent = "TIMES UP!";
    }
    
}


// for easy see the result
// card_container_display.style.display = "none";
// part_1_done = true;


let part_2_time_id;

part_2_time_id = setInterval(function(){
    if(part_1_done == true){
        // 關閉 part 2 的setInterval
        clearInterval(part_2_time_id);
        
        let elems = document.getElementsByClassName('checker-container');
        for (let i=0;i<elems.length;i+=1){
            elems[i].style.display = 'block';
        }

        loading.style.display = "none";


        countdown_timerId = setInterval(countdown, 1000);
    }
},1000);







//------------------- PART III - show-answer page ----------------------------------//

// card_container_display.style.display = "none";

// let elems = document.getElementsByClassName('checker-container');
// for (let i=0;i<elems.length;i+=1){
//     elems[i].style.display = 'none';
// }

let part_3_done = false;


let show_answer_group = document.querySelector(".show-answer-group");
let show_answer_box = show_answer_group.children[0];

let correct = "margin: 2px; border: 4.5px rgb(55, 245, 110) solid; border-radius: 5px;";
let wrong = "margin: 2px; border: 4.5px red solid; border-radius: 5px; opacity: 0.8;";

let score_bar = document.querySelector(".score");

let show_original_btn = document.querySelector(".show-original");

let correct_count = 0;

let original_btn_is_clicked = false;

// console.log(show_answer_group);
// show_answer_group.children[0].style.cssText = correct;
// show_answer_group.children[1].style.cssText = correct;

// checker_to_fill = checker_group.children[0];
// console.log(checker_group.childNodes);

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function check_answer(i) {
    let img = checker_group.children[i].src;

    img = img.slice(img.indexOf('card_pics'));
    if (img === "") img = "card_pics/poker-card-back.png";
    show_answer_group.children[i].src = img;

    if(img === shuffled_img[i]){
        show_answer_group.children[i].style.cssText = correct;
        correct_count++;
        score_bar.innerHTML = "Score: " + correct_count + "/52<br>Time used: " + time_used;
        // score_bar.textContent = `Score: ${correct_count}/52  Time used: ${time_used}`;
    }
    else{
        show_answer_group.children[i].style.cssText = wrong;
    }
    // console.log(img, shuffled_img[i]);
}

async function show_answer(){
    score_bar.innerHTML = "Score: 0/52<br>Time used: " + time_used;
    await sleep(100);

    for(let i=0; i<checker_group.childElementCount; i+=1){
        if(original_btn_is_clicked) break;

        check_answer(i);

        await sleep(50);
    }

    await sleep(10000);
    menu_btn.click();
}


function show_original(){
    correct_count = 0;
    if(show_original_btn.textContent === "Original"){
        original_btn_is_clicked = true;

        for(let i=0; i<checker_group.childElementCount; i+=1){
            let img = checker_group.children[i].src;
            img = img.slice(img.indexOf('card_pics'));
            if(img === shuffled_img[i]){
                correct_count++;
                score_bar.innerHTML = "Score: " + correct_count + "/52<br>Time used: " + time_used;
            }


            let original_img = shuffled_img[i];

            show_answer_group.children[i].src = original_img;
            show_answer_group.children[i].style.cssText = '';
        }

        show_original_btn.textContent = "Go back";
    }
    else{
        for(let i=0; i<checker_group.childElementCount; i+=1){
            check_answer(i);
        }

        show_original_btn.textContent = "Original";
    }
}

show_original_btn.addEventListener("click", show_original);



let part_3_time_id;

part_3_time_id = setInterval(function(){
    if(part_1_done == true && part_2_done == true){
        // 關閉 part 3 的setInterval
        clearInterval(part_3_time_id);
        
        loading.style.display = "none";


        let part_3_elems = document.getElementsByClassName('show-answer-container')
        for (let i=0;i<part_3_elems.length;i+=1){
            part_3_elems[i].style.display = 'block';
        }

        
        show_answer(checker_to_fill);

    }

},1000);