require 'bundler'
Bundler::GemHelper.install_tasks

desc "update ceedling versions in gem; assumes ceedling up-to-date"
task :update_versions do
  versions = {}
  # There's an extra line at the begining, but who cares.
  full_version_info = nil
  Dir.chdir("new_project") { full_version_info = `rake version` }
  full_version_info.each_line do |line|
    line = line.split("::")
    versions[line.first.strip.upcase] = line.last.strip
  end
  require "erb"
  result = ERB.new(File.read("lib/ceedling/version.rb.erb")).result(binding)
  File.open("lib/ceedling/version.rb", "wb+") { |f| f.puts result }
end
