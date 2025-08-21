jQuery(function () {
Highcharts.chart('container', {
		credits: {
			enabled: false
		},
		exporting: {
			enabled: false
		},
		chart: {
			type: 'line'
		},
		title: {
			text: 'Daily Total No. of Registered User'
		},
		subtitle: {
			text: ''
		},
		xAxis: {
			title: {
				text: 'Week'
			},
			min:0,
			max:5,
			scrollbar:{
				enabled: true	
			},
			categories: ['week 1','week 2','week 3','week 4','week 5']
		},
		yAxis: {
			title: {
				text: 'Weightage'
			}
		},
		plotOptions: {
			line: {
				dataLabels: {
					enabled: true
				},
				enableMouseTracking: true
			}
		},
		series: [{
			name: 'Planned',
			data: [0.0006244,0.0012488,0.0018732,0.00262248,0.00324688]
		}, {
			name: 'Actual',
			data: [0.00043551,0.00076062,0.00138502,0.0021343]
		}]
	});
});