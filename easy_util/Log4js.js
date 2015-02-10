var log4js = require('log4js');

log4js.configure({
    appenders: [
        { type: 'console' },
        {
            type: 'dateFile',
            filename: '/data/mcplog/logs/mcplog',
            pattern: "_yyyy-MM-dd.log",
            maxLogSize: 10240,
            alwaysIncludePattern: true,
            backups: 4,
            category: 'logger'
        }
    ],
    replaceConsole: true
});

module.exports = log4js.getLogger('logger');