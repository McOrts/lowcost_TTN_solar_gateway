pm.test("Status code is 200", function () {
    pm.response.to.have.status(200);
});

pm.test("It´s alive", function () {
    var jsonData = pm.response.json();
    var info = jsonData["mcorts-rak7258-auto"];
    pm.expect(info.online).equals(true);
    console.log(info.last_seen);
});
