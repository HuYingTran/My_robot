const char *indexHtml = R"literal(
  <!DOCTYPE html>
  <link rel='icon' href='/favicon.ico' sizes='any'>
  <body style='width:480px'>
    <h2>ESP Firmware Update</h2>
    <form method='POST' enctype='multipart/form-data' id='upload-form'>
      <input type='file' id='file' name='update'>
      <input type='submit' value='Update'>
    </form>
    <br>
    <div id='prg' style='width:0;color:white;text-align:center'>0%</div>
    
    <h2>Arduino Control</h2>
    <button id="btnForward">Tiến</button>
    <button id="btnBackward">Lùi</button>
    <button id="btnLeft">Trái</button>
    <button id="btnRight">Phải</button>
  </body>
  <script>
    // Phần firmware update
    var prg = document.getElementById('prg');
    var form = document.getElementById('upload-form');
    form.addEventListener('submit', el => {
      prg.style.backgroundColor = 'blue';
      el.preventDefault();
      var data = new FormData(form);
      var req = new XMLHttpRequest();
      var fsize = document.getElementById('file').files[0].size;
      req.open('POST', '/update?size=' + fsize);
      req.upload.addEventListener('progress', p => {
        let w = Math.round(p.loaded / p.total * 100) + '%';
        if (p.lengthComputable) {
          prg.innerHTML = w;
          prg.style.width = w;
        }
        if (w == '100%') prg.style.backgroundColor = 'black';
      });
      req.send(data);
    });

    // Phần điều khiển Arduino
    const sendCommand = (command) => {
      fetch(`/control?cmd=${command}`)
        .then(response => {
          if (response.ok) {
            console.log(`Command ${command} sent successfully`);
          } else {
            console.error(`Error sending command ${command}`);
          }
        });
    };

    document.getElementById('btnForward').addEventListener('click', () => sendCommand('forward'));
    document.getElementById('btnBackward').addEventListener('click', () => sendCommand('backward'));
    document.getElementById('btnLeft').addEventListener('click', () => sendCommand('left'));
    document.getElementById('btnRight').addEventListener('click', () => sendCommand('right'));
  </script>
)literal";
