function sleep(milliseconds) {
	const date = Date.now();
	let currentDate = null;
	do {
	  currentDate = Date.now();
	} while (currentDate - date < milliseconds);
  }

async function printTime() {
	while (true) {
		//[a-zA-Z]{3},\s\d{2}\s[a-zA-Z]{3}\s\d{4}\s\d{2}:\d{2}:\d{2}\sGMT
		var msg = "msg:- Tue, 09 Nov 2021 22:44:30 GMT|MOCHA_LOG|[d2ab4c10-41aa-11ec-9f1f-e17c7c74b71d:f890d5d0-41aa-11ec-b9ec-5d756f3002bb]: Forced garbage cleanup.\n\n\n 4 passing (909ms)\n\nTue, 09 Nov 2021 22:44:30 GMT|SERVICE_LOG|[d2ab4c10-41aa-11ec-9f1f-e17c7c74b71d:f890d5d0-41aa-11ec-b9ec-5d756f3002bb]: Finished mocha test.\nTue, 09 Nov 2021 22:44:30 GMT|SERVICE_LOG|[d2ab4c10-41aa-11ec-9f1f-e17c7c74b71d:f890d5d0-41aa-11ec-b9ec-5d756f3002bb]: 11039: Done processing job for user pin: L60843841_patchuser_001 from queue: d2ab4c10-41aa-11ec-9f1f-e17c7c74b71d_queue level:info region:blackberry @version:1 @timestamp:Nov 9, 2021 @ 17:44:30.720 app:espressobar2worker4worker_service _id:OP_fBn0BNxJnyCXkz5_h _type:_doc _index:logs-performance-lab-espressobar-000019 _score: -"
		var tokens = msg.split(/[a-zA-Z]{3},\s\d{2}\s[a-zA-Z]{3}\s\d{4}\s\d{2}:\d{2}:\d{2}\sGMT/);
		console.info(tokens);
		// console.info("INFO: Hello, the time is now " + Date() + '\n\nEnd\n\&\n"\n');
		// console.warn("WARN: Hello, the time is now " + Date());
		// console.error("ERROR: Hello, the time is now " + Date());
		// console.error("");
		console.log('Welcome to My Console,');
		await sleep(30000);
	};
}

printTime()